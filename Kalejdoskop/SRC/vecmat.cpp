#include "vecmat.h"

Matrix get_mreflection_matrix(double angle) {
    double m = tan(angle * (3.1415926 / 180));
    double m2 = m * m;

    Matrix tmp;
    tmp.data[0][0] = (1 - m2) / (1 + m2);
    tmp.data[0][1] = (2 * m) / (1 + m2);
    tmp.data[1][0] = (2 * m) / (1 + m2);
    tmp.data[1][1] = (m2 - 1) / (1 + m2);

    return tmp;
}

Matrix get_rotation_matrix(double angle) {
    float alpha_rad = angle * (3.1415926 / 180);       //  Nie zapomniec o konwersji deg -> rad

    Matrix tmp;
    tmp.data[0][0] = cos(alpha_rad);
    tmp.data[0][1] = -1 * sin(alpha_rad);
    tmp.data[1][0] = sin(alpha_rad);
    tmp.data[1][1] = cos(alpha_rad);

    return tmp;
}

Matrix get_translation_matrix(double x, double y) {
    Matrix tmp;

    tmp.data[0][0] = 1;
    tmp.data[0][2] = x;
    tmp.data[1][2] = y;
    tmp.data[1][1] = 1;

    return tmp;
}

Matrix get_xreflection_matrix() {
    Matrix tmp;
    tmp.data[0][0] = -1;
    tmp.data[1][1] = 1;

    return tmp;
}

Vector::Vector()
{
    data[0] = 0.0; data[1] = 0.0; data[2] = 1.0;
}

void Vector::Print(void)
{
    printf("(%2.3lf,%2.3lf,%2.3lf)\n", data[0], data[1], data[2]);
}

void Vector::Set(double d1, double d2)
{
    data[0] = d1; data[1] = d2;
}

double Vector::GetX()
{
    return data[0];
}

double Vector::GetY()
{
    return data[1];
}

Matrix::Matrix()
{
    data[0][0] = 0.0; data[0][1] = 0.0; data[0][2] = 0.0;
    data[1][0] = 0.0; data[1][1] = 0.0; data[1][2] = 0.0;
    data[2][0] = 0.0; data[2][1] = 0.0; data[2][2] = 1.0;
}

void Matrix::Print(void)
{
    printf("\n|%2.3lf,%2.3lf,%2.3lf|\n", data[0][0], data[0][1], data[0][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[1][0], data[1][1], data[1][2]);
    printf("|%2.3lf,%2.3lf,%2.3lf|\n", data[2][0], data[2][1], data[2][2]);
}

Matrix Matrix::operator* (const Matrix gMatrix)
{
    int i, j, k;
    Matrix tmp;

    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
        {
            tmp.data[i][j] = 0.0;
            for (k = 0; k < 3; k++)
                tmp.data[i][j] = tmp.data[i][j] + (data[i][k] * gMatrix.data[k][j]);
        }
    return tmp;
}

Vector operator* (const Matrix gMatrix, const Vector gVector)
{
    unsigned int i, j;
    Vector tmp;

    for (i = 0; i < 3; i++)
    {
        tmp.data[i] = 0.0;
        for (j = 0; j < 3; j++) tmp.data[i] = tmp.data[i] + (gMatrix.data[i][j] * gVector.data[j]);
    }
    return tmp;
}

int mirror(int index, int width, int height, Matrix matrix, double angle){
    //index += 1;
    double x = (index % width);
    double y = (height - (int)(index / width));

    Vector vector;
    vector.Set(x, y);

    vector = matrix * vector;

    Matrix transform = get_translation_matrix(-width / 2, -height / 2) * get_xreflection_matrix() * get_translation_matrix(width / 2, height / 2);

    vector = get_rotation_matrix(-angle) * get_translation_matrix(width / 2, height / 2) * vector;

    if (vector.GetY() > 0) return -1;

    vector = get_translation_matrix(-width / 2, -height / 2) * get_rotation_matrix(angle) * get_xreflection_matrix() * vector;


    double new_x = vector.GetX();
    double new_y = vector.GetY();

    double m = tan(angle * (3.1415926 / 180));

    if (new_x <= (-width / 2)) { return -1; }
    if (new_x >= (width / 2)) { return -1; }
    if (new_y <= (- height / 2)) { return -1; }
    if (new_y > new_x*m) { return -1; }

    new_y = height - new_y;

    //index = (new_y-2) * width + new_x-1;
    index = (int)(new_y * width + new_x);

    return index;
}