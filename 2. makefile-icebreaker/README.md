# Mini Makefile Icebreaker (Static vs Shared)

**Goal (10–15 min):** Build one tiny library two ways (static `.a` and shared `.so`) and link two small apps.
Then share *1 slide* with what you discovered.

## Files
- `math.h` — header
- `add.c`  — library function `add`
- `main.c` — app that calls `add`
- `Makefile` — super small with targets:
  - `libmath.a` (static), `libmath.so` (shared)
  - `app_static` (uses `libmath.a`), `app_shared` (uses `libmath.so`)
  - `run_static`, `run_shared`, `clean`

## Try it
```bash
make run_static     # builds libmath.a + app_static, then runs it
make run_shared     # builds libmath.so + app_shared (with rpath), then runs it
make clean
```
> If `app_shared` can't find the `.so` on your machine, ensure the Makefile’s rpath flag is present;
  otherwise run with: `LD_LIBRARY_PATH=. ./app_shared 8 9`.

## Your 1-slide share-out (pair)
**Title:** Static vs Shared — What surprised us  
**Bullets (hit at least 3):**
- How building `.a` and `.so` differs (commands/flags).
- What the linker needed at build time vs what the loader needs at run time.
- How we made the shared app run without setting `LD_LIBRARY_PATH` (hint: rpath).
- Any error we hit (and the fix).
- One tip you’d give next year’s class.

Add a tiny screenshot of your terminal showing each app running.
