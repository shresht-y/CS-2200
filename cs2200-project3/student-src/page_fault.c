#include "mmu.h"
#include "pagesim.h"
#include "swapops.h"
#include "stats.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/**
 * --------------------------------- PROBLEM 6 --------------------------------------
 * Checkout PDF section 7 for this problem
 * 
 * Page fault handler.
 * 
 * When the CPU encounters an invalid address mapping in a page table, it invokes the 
 * OS via this handler. Your job is to put a mapping in place so that the translation 
 * can succeed.
 * 
 * @param addr virtual address in the page that needs to be mapped into main memory.
 * 
 * HINTS:
 *      - You will need to use the global variable current_process when
 *      altering the frame table entry.
 *      - Use swap_exists() and swap_read() to update the data in the 
 *      frame as it is mapped in.
 * ----------------------------------------------------------------------------------
 */
void page_fault(vaddr_t addr) {
   // DONE: Get a new frame, then correctly update the page table and frame table

   //1. get the page table entry 
   vpn_t vpn = vaddr_vpn(addr);
   //uint16_t offset = vaddr_offset(addr);
   pte_t *page_entry = (pte_t*) (mem + PTBR * PAGE_SIZE) + vpn;

   //2. use free_frame() to get the PFN of a new frame
   pfn_t pfn = free_frame();

   if (pfn == 0) {
      //break in this case *for debugging*
   }
   //5. Update the mapping from VPN to the new PFN in the current process' page table
   page_entry->dirty=0;
   page_entry->pfn=pfn;
   page_entry->valid=1;
   //page_entry+=vpn;


   //3-4. check to see if there is an existing swap 
   if(swap_exists(page_entry)){
      swap_read(page_entry, mem + pfn * PAGE_SIZE);
   } else {
      memset(mem + pfn * PAGE_SIZE, 0, PAGE_SIZE);
   }

   //6. Update the flags in the corresponding frame table entry 
   frame_table[pfn].mapped=1;
   frame_table[pfn].process=current_process;
   frame_table[pfn].protected=0;
   //frame_table[pfn].ref_count=0;
   frame_table[pfn].referenced=1;
   frame_table[pfn].vpn=vpn;

   stats.page_faults++;
}

#pragma GCC diagnostic pop
