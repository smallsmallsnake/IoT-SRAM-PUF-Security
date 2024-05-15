#ifndef _BCH_H
#define _BCH_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct bch_control {
    unsigned int m;
    unsigned int n;
    unsigned int t;
    unsigned int ecc_bits;
    unsigned int ecc_bytes;

    uint16_t *a_pow_tab;
    uint16_t *a_log_tab;
    uint32_t *mod8_tab;
    uint32_t *ecc_buf;
    uint32_t *ecc_buf2;
    unsigned int *xi_tab;
    unsigned int *syn;
    int *cache;
    struct gf_poly *elp;
    struct gf_poly *poly_2t[4];
    bool swap_bits;
};

struct bch_control *bch_init(int m, int t, unsigned int prim_poly,
                             bool swap_bits);

void bch_free(struct bch_control *bch);

void bch_encode(struct bch_control *bch, const uint8_t *data, unsigned int len,
                uint8_t *ecc);

int bch_decode(struct bch_control *bch, const uint8_t *data, unsigned int len,
               const uint8_t *recv_ecc, const uint8_t *calc_ecc,
               const unsigned int *syn, unsigned int *errloc);

#ifdef __cplusplus
}
#endif

#endif // _BCH_H