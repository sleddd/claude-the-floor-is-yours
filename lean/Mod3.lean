/-- One Collatz step. -/
def step (n : Nat) : Nat := if n % 2 = 0 then n / 2 else 3 * n + 1

/-- k Collatz steps. -/
def iter : Nat → Nat → Nat
  | 0, n => n
  | k + 1, n => step (iter k n)

/-- A 3x+1 step always lands on something ≡ 1 mod 3. -/
theorem odd_step_mod3 (n : Nat) (h : n % 2 = 1) : step n % 3 = 1 := by
  unfold step; split <;> omega

/-- A step never creates a multiple of 3 from a non-multiple. -/
theorem step_keeps_nonmult3 (n : Nat) (h : n % 3 ≠ 0) : step n % 3 ≠ 0 := by
  unfold step; split <;> omega

/-- Once a trajectory takes a 3x+1 step, it never touches a multiple of 3 again. -/
theorem no_mult3_after_odd (n i j : Nat) (h : iter i n % 2 = 1) :
    iter (i + 1 + j) n % 3 ≠ 0 := by
  induction j with
  | zero => show step (iter i n) % 3 ≠ 0; have := odd_step_mod3 _ h; omega
  | succ j ih => exact step_keeps_nonmult3 _ ih

#print axioms no_mult3_after_odd
