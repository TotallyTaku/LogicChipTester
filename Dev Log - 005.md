---
logNum: 5
tags:
  - project
  - ICTESTER
creation_date: 2026-07-30
---

# IC Tester - Dev Log 005

## What I did

 -  Added comments to divide code into sections to make navigating easier
 - Wrote test functions which return bool if chip passes or fails test
 - More refactoring to make readability easier
 - Added structures to support all chips I personally have and can test with 1-input and 2-input based outputs
 - Expanded upon the Serial-based menu should be ALMOST working
## What worked

 - Everything was relatively easy to implement up until this point
## Problems
 - 400 lines of code, its getting harder and harder to keep track of everything
 - Iterating NICELY through ideally 1 array that holds all the chips (which are different structs) is proving to be very difficulty
	 - Reading up on enums, and unions to try and make this work

- I probably need to start adding delays to make sure things happen sequentially as expected in my testing functions. (**1ms delay should be fine since gates propagate in ns**)
## What we learned
 - unions are a thing
	 - They can be used to *hopefully* make one nice struct. Then we make an array with that nice struct and in theory have "different" types of elements in the array though technically its more like wrapping around it and casting it correctly but whatever
