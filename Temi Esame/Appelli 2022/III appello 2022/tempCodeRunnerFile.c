
    int r = 3, c = 3, d = 2;
    matTri = (int ***)malloc(d * d * sizeof(int **));
    for (k = 0; k < (d * d); k++)
    {
        matTri[k] = (int **)malloc(r * sizeof(int *));
        for (i = 0; i < r; i++)
        {
            matTri[k][i] = (int *)malloc(c * sizeof(int));
        }
    }

    matTri[0][0][0] = 18;
    matTri[0][0][1] = 19;
    matTri[0][0][2] = 20;
    matTri[0][1][0] = 9;
    matTri[0][1][1] = 10;
    matTri[0][1][2] = 11;
    matTri[0][2][0] = 0;
    matTri[0][2][1] = 1;
    matTri[0][2][2] = 2;

    matTri[1][0][0] = 12;
    matTri[1][0][1] = 13;
    matTri[1][0][2] = 14;
    matTri[1][1][0] = 6;
    matTri[1][1][1] = 7;
    matTri[1][1][2] = 8;
    matTri[1][2][0] = 0;
    matTri[1][2][1] = 1;
    matTri[1][2][2] = 2;

    matTri[2][0][0] = 6;
    matTri[2][0][1] = 7;
    matTri[2][0][2] = 8;
    matTri[2][1][0] = 3;
    matTri[2][1][1] = 4;
    matTri[2][1][2] = 5;
    matTri[2][2][0] = 0;
    matTri[2][2][1] = 1;
    matTri[2][2][2] = 2;

    matTri[3][0][0] = 0;
    matTri[3][0][1] = 1;
    matTri[3][0][2] = 2;
    matTri[3][1][0] = 0;
    matTri[3][1][1] = 1;
    matTri[3][1][2] = 2;
    matTri[3][2][0] = 0;
    matTri[3][2][1] = 1;
    matTri[3][2][2] = 2;