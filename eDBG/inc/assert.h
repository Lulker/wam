auto assert( auto f ){ if(f) return f; throw;};
auto assert_lt( auto f, auto c ){assert(f<c);return f;};
auto assert_gt( auto f, auto c ){assert(f>c);return f;};
auto assert_leq( auto f, auto c ){assert(f<=c);return f;};
auto assert_geq( auto f, auto c ){assert(f>=c);return f;};
auto assert_eq( auto f, auto c ){assert(f==c);return f;};
auto assert_neq( auto f, auto c ){assert(f!=c);return f;};
