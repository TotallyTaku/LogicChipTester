---
logNum: 3
tags:
  - project
  - ICTESTER
creation_date: 2026-06-28
---

# IC Tester - Dev Log 003

## What I did

 - Removed unused constants causing issues
 - Added new structures
 - Refactored key functions again like compare, run, setup and test
 - Programmed key layout functionalities for basic well known gates (not finished)
## What worked
 -  Making everything into structures made adding new chips much easier
	 - Functions are now a decent bit more difficult to write
## Problems
 - 74LS02N(quad 2-input NOR gate) has an unusual pin layout.
	 - This made me realize I need to redefine `two_input_gate_pin_setup` and make it modular so that I can more easily do any other chips that may or may not have funky layouts

- My function names are so HORRIBLE I keep forgetting what does what and what its supposed to return what.
	- I thought about hoping on LucidChart and drawing it all out but I think just renaming them for now should do the trick

- Had to do a lot of functions to test various chips
	- Seems easier to make each chip part of a structure with the chip's necessary information to be tested. Then make a generic tester that tests a chip of that type like a quad 2-input chip.

## What we learned
 - Structure size is determined by its members. 
	 - A struct with 3 ints will have size 3 x 4 bytes or 12 bytes
		 - This makes sense but I had never looked at it before

- Making structs goes a long way when we want to make things modular. 

- Generic testers and generic functions tied to a struct seem to be much more efficient and easier to read and code instead of niche one of functions. 

## Next to implement

- Similarly functionality for the SingleInputGates to the current QuadTwoInputGates
	- redo their run, and their setups to match the QuadDoubleInput way.

- Make the structures for Triple Input Chips
- Make structures for Quad Input Chips

- Make the serial functions to have an Interface to interact with