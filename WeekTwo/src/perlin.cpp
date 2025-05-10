#include "perlin.h"
void perlin::permute(int* p, int n)
{
    for (int i = n-1; i > 0; i--)
    {
        int target = rand_int(0, i);
        int tmp = p[i];
        p[i] = p[target];
        p[target] = tmp;
    }
}

void perlin::perlin_generate_perm(int* p)
{
    for (int i = 0; i < point_count; i++)
    {
        p[i] = i;
    }
    permute(p, point_count);
}

perlin::perlin()
{
    for (int i = 0; i < point_count; i++)
    {
        randfloat[i] = rand_f();
    }
    perlin_generate_perm(perm_x);
    perlin_generate_perm(perm_y);
    perlin_generate_perm(perm_z);
}

float perlin::noise(const point3& p) const {
        float u = p.x() - std::floor(p.x());
        float v = p.y() - std::floor(p.y());
        float w = p.z() - std::floor(p.z());
        u = u*u*(3-2*u);
        v = v*v*(3-2*v);
        w = w*w*(3-2*w);

        int i = int(std::floor(p.x()));
        int j = int(std::floor(p.y()));
        int k = int(std::floor(p.z()));
        float c[2][2][2];

        for (int di=0; di < 2; di++)
            for (int dj=0; dj < 2; dj++)
                for (int dk=0; dk < 2; dk++)
                    c[di][dj][dk] = randfloat[
                        perm_x[(i+di) & 255] ^
                        perm_y[(j+dj) & 255] ^
                        perm_z[(k+dk) & 255]
                    ];

        return trilinear_interp(c, u, v, w);
    }
float perlin::trilinear_interp(float c[2][2][2], float u, float v, float w)
{
    float accum = 0.0f;
    for (int i=0; i < 2; i++)
        for (int j=0; j < 2; j++)
            for (int k=0; k < 2; k++)
                accum += (i*u + (1-i)*(1-u))
                       * (j*v + (1-j)*(1-v))
                       * (k*w + (1-k)*(1-w))
                       * c[i][j][k];

    return accum;
}