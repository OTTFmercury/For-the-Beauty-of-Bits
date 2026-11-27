

constexpr int N = 1515;

namespace Array_Hash_Big_To_Small {
	template <typename T, T mod, T base>
    void init_power (int len, T power[N]) {
        power[0] = 1;
        for (int i = 1; i <= len; i++) {
            power[i] = power[i - 1] * base % mod;
        }
    }

	template <typename T, T mod, T base>
    void init_hash (T arr[N], int len, T hash[N]) {
        for (int i = len; i >= 1; i--) {
            hash[i] = (hash[i + 1] * base % mod + arr[i]) % mod;
        }
    }

	template <typename T, T mod, T base>
    T hash (T power[N], T hash[N], int l, int r) {
        return ((hash[l] - hash[r + 1] * power[r - l + 1] % mod) % mod + mod) % mod;
    }
}

constexpr int Mod_Num = 2;

namespace Multi_Array_Hash_Big_To_Small {
    template <typename T, int divisor_id>
    void single_init_power (int len, T power[Mod_Num][N]) {
        Array_Hash_Big_To_Small::init_power<T, Mod[divisor_id], Base[divisor_id]> (len, power[divisor_id]);
    }

    template <typename T, int divisor_id>
    void multi_init_power (int len, T power[Mod_Num][N]) {
        Array_Hash_Big_To_Small::init_power<T, Mod[divisor_id], Base[divisor_id]> (len, power[divisor_id]);
        if constexpr (divisor_id > 0) {
            multi_init_power<T, divisor_id - 1>(len, power);
        }
    }

    template <typename T, int divisor_id>
    void single_init_hash (T arr[N], int len, T hash[Mod_Num][N]) {
        Array_Hash_Big_To_Small::init_hash<T, Mod[divisor_id], Base[divisor_id]> (arr, len, hash[divisor_id]);
    }

    template <typename T, int divisor_id>
    void multi_init_hash (T arr[N], int len, T hash[Mod_Num][N]) {
        Array_Hash_Big_To_Small::init_hash<T, Mod[divisor_id], Base[divisor_id]> (arr, len, hash[divisor_id]);
        if constexpr (divisor_id > 0) {
            multi_init_hash<T, divisor_id - 1> (arr, len, hash);
        }
    }

    template <typename T, int divisor_id>
    T single_hash (T power[Mod_Num][N], T hash[Mod_Num][N], int l, int r) {
        return Array_Hash_Big_To_Small::hash<T, Mod[divisor_id], Base[divisor_id]> (power[divisor_id], hash[divisor_id], l, r);
    }

    template <typename T, int divisor_id, T mult>
    T multi_hash (T power[Mod_Num][N], T hash[Mod_Num][N], int l, int r) {
        T ans = Array_Hash_Big_To_Small::hash<T, Mod[divisor_id], Base[divisor_id]> (power[divisor_id], hash[divisor_id], l, r);
        if constexpr (divisor_id > 0) {
            ans = ans * mult + multi_hash<T, divisor_id - 1, mult> (power, hash, l, r);
        }
        return ans;
    }
}