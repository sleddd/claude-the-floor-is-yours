/-- Shortcut Collatz step for odd x: (3x+1)/2. -/
def T (x : Nat) : Nat := (3 * x + 1) / 2

def Titer : Nat → Nat → Nat
  | 0, x => x
  | j + 1, x => T (Titer j x)

/-- One climbing step: one factor of 2 traded for one factor of 3. -/
theorem climb (x j i m : Nat) (h : x + 1 = 3^j * 2^(i+1) * m) :
    x % 2 = 1 ∧ T x + 1 = 3^(j+1) * 2^i * m := by
  have e1 : 3^j * 2^(i+1) * m = 2 * (3^j * 2^i * m) := by rw [Nat.pow_succ]; ac_rfl
  have e2 : 3^(j+1) * 2^i * m = 3 * (3^j * 2^i * m) := by rw [Nat.pow_succ]; ac_rfl
  rw [e1] at h; rw [e2]; unfold T
  generalize 3^j * 2^i * m = A at *
  constructor <;> omega

/-- The trailing-ones fence: if n+1 = 2^k * m, the first k steps all climb,
    and after j of them x_j + 1 = 3^j * 2^(k-j) * m. -/
theorem fence (n k m : Nat) (h : n + 1 = 2^k * m) :
    ∀ j, j ≤ k → Titer j n + 1 = 3^j * 2^(k-j) * m := by
  intro j
  induction j with
  | zero => intro _; simp [Titer, h]
  | succ j ih =>
    intro hj
    have hk : k - j = (k - (j+1)) + 1 := by omega
    have prev := ih (by omega)
    rw [hk] at prev
    exact (climb _ j (k - (j+1)) m prev).2

/-- ...and every one of those first k values is odd, so each step really is 3x+1 then halve. -/
theorem fence_odd (n k m : Nat) (h : n + 1 = 2^k * m) (j : Nat) (hj : j < k) :
    Titer j n % 2 = 1 := by
  have prev := fence n k m h j (by omega)
  have hk : k - j = (k - (j+1)) + 1 := by omega
  rw [hk] at prev
  exact (climb _ j (k - (j+1)) m prev).1

theorem three_pow_odd (k : Nat) : 3^k % 2 = 1 := by
  induction k with
  | zero => rfl
  | succ k ih => rw [Nat.pow_succ]; omega

/-- If m is odd, the climb stops at exactly k: the value after k steps is even. -/
theorem fence_stops (n k m : Nat) (h : n + 1 = 2^k * m) (hm : m % 2 = 1) :
    Titer k n % 2 = 0 := by
  have e := fence n k m h k (Nat.le_refl k)
  simp only [Nat.sub_self, Nat.pow_zero, Nat.mul_one] at e
  have odd : (3^k * m) % 2 = 1 := by rw [Nat.mul_mod, three_pow_odd, hm]
  omega

#print axioms fence_stops
#print axioms fence_odd
