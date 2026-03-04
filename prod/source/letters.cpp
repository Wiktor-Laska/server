#include "letters.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <iostream>


// TODO:
//implement numbers, "Y", "J", ".', 
//implement coloring of text


//define A vao, vbo
GLuint vao_A;
GLuint vbo_pos_A;
GLuint vbo_col_A;

GLfloat pos_A[] = { //define A pos matrix
    -0.25f, -0.5f, 0.0f,     -0.1f,  -0.5f, 0.0f,     -0.1f,   0.5f, 0.0f,
    -0.1f,  -0.5f, 0.0f,     -0.1f,   0.5f, 0.0f,      0.0f,   0.5f, 0.0f,

     0.1f,  -0.5f, 0.0f,      0.25f, -0.5f, 0.0f,      0.1f,   0.5f, 0.0f,
     0.1f,  -0.5f, 0.0f,      0.1f,   0.5f, 0.0f,      0.0f,   0.5f, 0.0f,

    -0.1f,   0.3f, 0.0f,      0.1f,   0.3f, 0.0f,      0.1f,   0.5f, 0.0f,
    -0.1f,   0.3f, 0.0f,      0.1f,   0.5f, 0.0f,     -0.1f,   0.5f, 0.0f,

    -0.1f,  -0.2f, 0.0f,      0.1f,  -0.2f, 0.0f,      0.1f,   0.0f, 0.0f,
    -0.1f,  -0.2f, 0.0f,      0.1f,   0.0f, 0.0f,     -0.1f,   0.0f, 0.0f
};

GLfloat col_A[24*3]; //define A col matrix


//define B vao, vbo
GLuint vao_B;
GLuint vbo_pos_B;
GLuint vbo_col_B;

GLfloat pos_B[] = { //define B pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

    //dolne
    -0.1f,  -0.5f,  0.0f,     -0.1f,  -0.35f, 0.0f,      0.1f,  -0.45f, 0.0f,
    -0.1f,  -0.35f, 0.0f,      0.1f,  -0.45f, 0.0f,      0.1f,  -0.3f,  0.0f,

     0.1f,  -0.45f, 0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,
     0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,      0.25f, -0.2f,  0.0f,

     0.1f,  -0.3f,  0.0f,      0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,
     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.1f,  -0.05f, 0.0f,

     0.1f,  -0.2f,  0.0f,      0.1f,  -0.05f, 0.0f,     -0.1f,  -0.1f,  0.0f,
     0.1f,  -0.05f, 0.0f,     -0.1f,  -0.1f,  0.0f,      0.0f,   0.0f,  0.0f,

    //gorne
    -0.1f,   0.5f,  0.0f,     -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,
    -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,

     0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.25f,  0.2f,  0.0f,

     0.1f,   0.3f,  0.0f,      0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,
     0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,      0.1f,   0.05f, 0.0f,

     0.1f,   0.2f,  0.0f,      0.1f,   0.05f, 0.0f,     -0.1f,   0.15f, 0.0f,
     0.1f,   0.05f, 0.0f,     -0.1f,   0.15f, 0.0f,     -0.02f,  0.02f, 0.0f,

     //dziura
    -0.1f,  -0.1f,  0.0f,     -0.1f,   0.15f, 0.0f,      0.0f,   0.0f,  0.0f
};

GLfloat col_B[57*3]; //define B col matrix


//define C vao, vbo
GLuint vao_C;
GLuint vbo_pos_C;
GLuint vbo_col_C;

GLfloat pos_C[] = { //define C pos matrix
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,
    -0.25f, -0.2f,  0.0f,     -0.25f,  0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,

    //dol
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,
    -0.1f,  -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,

    -0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,
     0.0f,  -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,      0.05f, -0.5f,  0.0f,

     0.0f,  -0.35f, 0.0f,      0.05f, -0.5f,  0.0f,      0.15f, -0.4f,  0.0f,

     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.15f, -0.4f,  0.0f,
     0.1f,  -0.2f,  0.0f,      0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,

    //gora
    -0.25f,  0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,     -0.15f,  0.4f,  0.0f,
    -0.1f,   0.2f,  0.0f,     -0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,

    -0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,     -0.05f,  0.5f,  0.0f,
     0.0f,   0.35f, 0.0f,     -0.05f,  0.5f,  0.0f,      0.05f,  0.5f,  0.0f,

     0.0f,   0.35f, 0.0f,      0.05f,  0.5f,  0.0f,      0.15f,  0.4f,  0.0f,

     0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,      0.15f,  0.4f,  0.0f,
     0.1f,   0.2f,  0.0f,      0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f

};

GLfloat col_C[48*3]; //define C col matrix


//define D vao, vbo
GLuint vao_D;
GLuint vbo_pos_D;
GLuint vbo_col_D;

GLfloat pos_D[] = { //define D pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

    //przod
    -0.1f,  -0.5f,  0.0f,     -0.1f,  -0.35f, 0.0f,      0.1f,  -0.45f, 0.0f,
    -0.1f,  -0.35f, 0.0f,      0.1f,  -0.45f, 0.0f,      0.1f,  -0.3f,  0.0f,

     0.1f,  -0.45f, 0.0f,      0.1f,  -0.3f,  0.0f,      0.2f,  -0.35f, 0.0f,
     0.1f,  -0.3f,  0.0f,      0.2f,  -0.35f, 0.0f,      0.25f, -0.2f,  0.0f,//

    -0.1f,   0.5f,  0.0f,     -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,
    -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,

     0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,      0.2f,   0.35f, 0.0f,
     0.1f,   0.3f,  0.0f,      0.2f,   0.35f, 0.0f,      0.25f,  0.2f,  0.0f,//

     0.25f, -0.2f,  0.0f,      0.25f,  0.2f,  0.0f,      0.1f,   0.3f,  0.0f,
     0.25f, -0.2f,  0.0f,      0.1f,   0.3f,  0.0f,      0.1f,  -0.3f,  0.0f,
};

GLfloat col_D[36*3]; //define D col matrix


//define E vao, vbo
GLuint vao_E;
GLuint vbo_pos_E;
GLuint vbo_col_E;

GLfloat pos_E[] = { //define E pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

    //przod
     0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,
    -0.1f,  -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,     -0.1f,  -0.35f, 0.0f,

     0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,      0.25f,  0.35f, 0.0f,
    -0.1f,   0.5f,  0.0f,      0.25f,  0.35f, 0.0f,     -0.1f,   0.35f, 0.0f,

    -0.1f,   0.075f,0.0f,     -0.1f,  -0.075f,0.0f,      0.15f,  0.075f,0.0f,
    -0.1f,  -0.075f,0.0f,      0.15f,  0.075f,0.0f,      0.15f, -0.075f,0.0f

};

GLfloat col_E[24*3]; //define E col matrix


//define G vao, vbo
GLuint vao_G;
GLuint vbo_pos_G;
GLuint vbo_col_G;

GLfloat pos_G[] = { //define G pos matrix
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,
    -0.25f, -0.2f,  0.0f,     -0.25f,  0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,

    //dol
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,
    -0.1f,  -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,

    -0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,
     0.0f,  -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,      0.05f, -0.5f,  0.0f,

     0.0f,  -0.35f, 0.0f,      0.05f, -0.5f,  0.0f,      0.15f, -0.4f,  0.0f,

     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.15f, -0.4f,  0.0f,
     0.1f,  -0.2f,  0.0f,      0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,

    //gora
    -0.25f,  0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,     -0.15f,  0.4f,  0.0f,
    -0.1f,   0.2f,  0.0f,     -0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,

    -0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,     -0.05f,  0.5f,  0.0f,
     0.0f,   0.35f, 0.0f,     -0.05f,  0.5f,  0.0f,      0.05f,  0.5f,  0.0f,

     0.0f,   0.35f, 0.0f,      0.05f,  0.5f,  0.0f,      0.15f,  0.4f,  0.0f,

     0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,      0.15f,  0.4f,  0.0f,
     0.1f,   0.2f,  0.0f,      0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,
    //haczyk
     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.25f, -0.1f,  0.0f,
     0.1f,  -0.2f,  0.0f,      0.25f, -0.1f,  0.0f,      0.1f,  -0.1f,  0.0f,
     
     0.25f, -0.1f,  0.0f,      0.0f,  -0.1f,  0.0f,      0.25f,  0.0f,  0.0f,
     0.0f,  -0.1f,  0.0f,      0.25f,  0.0f,  0.0f,      0.0f,   0.0f,  0.0f
       

};

GLfloat col_G[60*3]; //define G col matrix


//define I vao, vbo
GLuint vao_I;
GLuint vbo_pos_I;
GLuint vbo_col_I;

GLfloat pos_I[] = { //define I pos matrix
    //kreska
    -0.075f,-0.5f,  0.0f,     0.075f, -0.5f,  0.0f,      0.075f, 0.5f,  0.0f,
    -0.075f,-0.5f,  0.0f,    -0.075f,  0.5f,  0.0f,      0.075f, 0.5f,  0.0f
};

GLfloat col_I[6*3]; //define G col matrix


//define K vao, vbo
GLuint vao_K;
GLuint vbo_pos_K;
GLuint vbo_col_K;

GLfloat pos_K[] = { //define K pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

     0.25f,  0.5f,  0.0f,      0.1f,   0.5f,  0.0f,     -0.1f,  -0.1f,  0.0f,
     0.1f,   0.5f,  0.0f,     -0.1f,  -0.1f,  0.0f,     -0.1f,   0.05f, 0.0f,

     0.25f, -0.5f,  0.0f,      0.1f,  -0.5f,  0.0f,     -0.1f,   0.1f,  0.0f,
     0.1f,  -0.5f,  0.0f,     -0.1f,   0.1f,  0.0f,     -0.1f,  -0.05f, 0.0f
};

GLfloat col_K[18*3]; //define K col matrix


//define L vao, vbo
GLuint vao_L;
GLuint vbo_pos_L;
GLuint vbo_col_L;

GLfloat pos_L[] = { //define L pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

    //przod
     0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,
    -0.1f,  -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,     -0.1f,  -0.35f, 0.0f

};

GLfloat col_L[12*3]; //define L col matrix


//define N vao, vbo
GLuint vao_N;
GLuint vbo_pos_N;
GLuint vbo_col_N;

GLfloat pos_N[] = { //define N pos matrix
    //kreski
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

     0.25f, -0.5f,  0.0f,      0.1f,  -0.5f,  0.0f,      0.1f,   0.5f,  0.0f,
     0.25f, -0.5f,  0.0f,      0.25f,  0.5f,  0.0f,      0.1f,   0.5f,  0.0f,

    //skos
     0.25f, -0.5f,  0.0f,      0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
     0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,     -0.25f,  0.5f,  0.0f

};

GLfloat col_N[18*3]; //define N col matrix


//define O vao, vbo
GLuint vao_O;
GLuint vbo_pos_O;
GLuint vbo_col_O;

GLfloat pos_O[] = { //define O pos matrix
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,
    -0.25f, -0.2f,  0.0f,     -0.25f,  0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,

    //dol
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,
    -0.1f,  -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,

    -0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,
     0.0f,  -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,      0.05f, -0.5f,  0.0f,

     0.0f,  -0.35f, 0.0f,      0.05f, -0.5f,  0.0f,      0.15f, -0.4f,  0.0f,

     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.15f, -0.4f,  0.0f,
     0.1f,  -0.2f,  0.0f,      0.15f, -0.4f,  0.0f,      0.0f,  -0.35f, 0.0f,

    //gora
    -0.25f,  0.2f,  0.0f,     -0.1f,   0.2f,  0.0f,     -0.15f,  0.4f,  0.0f,
    -0.1f,   0.2f,  0.0f,     -0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,

    -0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,     -0.05f,  0.5f,  0.0f,
     0.0f,   0.35f, 0.0f,     -0.05f,  0.5f,  0.0f,      0.05f,  0.5f,  0.0f,

     0.0f,   0.35f, 0.0f,      0.05f,  0.5f,  0.0f,      0.15f,  0.4f,  0.0f,

     0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,      0.15f,  0.4f,  0.0f,
     0.1f,   0.2f,  0.0f,      0.15f,  0.4f,  0.0f,      0.0f,   0.35f, 0.0f,

     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.1f,   0.2f,  0.0f,
     0.25f, -0.2f,  0.0f,      0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f

};

GLfloat col_O[54*3]; //define O col matrix


//define P vao, vbo
GLuint vao_P;
GLuint vbo_pos_P;
GLuint vbo_col_P;

GLfloat pos_P[] = { //define P pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    //brzuszek
    -0.1f,   0.5f,  0.0f,     -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,
    -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,

     0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.25f,  0.2f,  0.0f,

     0.1f,   0.3f,  0.0f,      0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,
     0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,      0.1f,   0.0f,  0.0f,

     0.1f,   0.2f,  0.0f,      0.1f,   0.0f,  0.0f,     -0.1f,   0.1f,  0.0f,
     0.1f,   0.0f,  0.0f,     -0.1f,   0.1f,  0.0f,     -0.02f,  0.0f,  0.0f,

    -0.1f,  -0.05f, 0.0f,     -0.1f,   0.1f,  0.0f,      0.1f,   0.0f,  0.0f

};

GLfloat col_P[33*3]; //define P col matrix


//define R vao, vbo
GLuint vao_R;
GLuint vbo_pos_R;
GLuint vbo_col_R;

GLfloat pos_R[] = { //define R pos matrix
    //kreska
    -0.25f, -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.25f, -0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,
    //brzuszek
    -0.1f,   0.5f,  0.0f,     -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,
    -0.1f,   0.35f, 0.0f,      0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,

     0.1f,   0.45f, 0.0f,      0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.25f,  0.2f,  0.0f,

     0.1f,   0.3f,  0.0f,      0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,
     0.25f,  0.2f,  0.0f,      0.1f,   0.2f,  0.0f,      0.1f,   0.0f,  0.0f,

     0.1f,   0.2f,  0.0f,      0.1f,   0.0f,  0.0f,     -0.1f,   0.1f,  0.0f,
     0.1f,   0.0f,  0.0f,     -0.1f,   0.1f,  0.0f,     -0.02f,  0.0f,  0.0f,

    -0.1f,  -0.05f, 0.0f,     -0.1f,   0.1f,  0.0f,      0.1f,   0.0f,  0.0f,
    //kreska
     0.25f, -0.5f,  0.0f,      0.15f, -0.5f,  0.0f,      0.0f,   0.0f,  0.0f,
     0.15f, -0.5f,  0.0f,      0.0f,   0.0f,  0.0f,     -0.15f,  0.0f,  0.0f

};

GLfloat col_R[39*3]; //define R col matrix


//define S vao, vbo
GLuint vao_S;
GLuint vbo_pos_S;
GLuint vbo_col_S;

GLfloat pos_S[] = { //define S pos matrix
    //kreska
    -0.25f, -0.25f, 0.0f,     -0.15f, -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,
    -0.15f, -0.2f,  0.0f,     -0.15f, -0.4f,  0.0f,     -0.05f, -0.35f, 0.0f,

    -0.15f, -0.4f,  0.0f,     -0.05f, -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,
    -0.05f, -0.35f, 0.0f,     -0.05f, -0.5f,  0.0f,      0.05f, -0.5f,  0.0f,

    -0.05f, -0.35f, 0.0f,      0.05f, -0.5f,  0.0f,      0.05f, -0.35f, 0.0f,
     0.05f, -0.5f,  0.0f,      0.05f, -0.35f, 0.0f,      0.15f, -0.4f,  0.0f,

     0.05f, -0.35f, 0.0f,      0.15f, -0.4f,  0.0f,      0.15f, -0.25f, 0.0f,
     0.15f, -0.4f,  0.0f,      0.15f, -0.25f, 0.0f,      0.25f, -0.25f, 0.0f,

     0.15f, -0.25f, 0.0f,      0.25f, -0.25f, 0.0f,      0.25f, -0.1f,  0.0f,
     0.25f, -0.25f, 0.0f,      0.25f, -0.1f,  0.0f,      0.1f,  -0.1f,  0.0f,

     0.25f, -0.1f,  0.0f,      0.1f,  -0.1f,  0.0f,      0.1f,  0.05f,  0.0f,
     0.1f,  -0.1f,  0.0f,      0.1f,   0.05f, 0.0f,     -0.1f, -0.05f,  0.0f,



     0.25f,  0.25f, 0.0f,      0.15f,  0.2f,  0.0f,      0.15f,  0.4f,  0.0f,
     0.15f,  0.2f,  0.0f,      0.15f,  0.4f,  0.0f,      0.05f,  0.35f, 0.0f,

     0.15f,  0.4f,  0.0f,      0.05f,  0.35f, 0.0f,      0.05f,  0.5f,  0.0f,
     0.05f,  0.35f, 0.0f,      0.05f,  0.5f,  0.0f,     -0.05f,  0.5f,  0.0f,

     0.05f,  0.35f, 0.0f,     -0.05f,  0.5f,  0.0f,     -0.05f,  0.35f, 0.0f,
    -0.05f,  0.5f,  0.0f,     -0.05f,  0.35f, 0.0f,     -0.15f,  0.4f,  0.0f,

    -0.05f,  0.35f, 0.0f,     -0.15f,  0.4f,  0.0f,     -0.15f,  0.25f, 0.0f,
    -0.15f,  0.4f,  0.0f,     -0.15f,  0.25f, 0.0f,     -0.25f,  0.25f, 0.0f,

    -0.15f,  0.25f, 0.0f,     -0.25f,  0.25f, 0.0f,     -0.25f,  0.1f,  0.0f,
    -0.25f,  0.25f, 0.0f,     -0.25f,  0.1f,  0.0f,     -0.1f,   0.1f,  0.0f,

    -0.25f,  0.1f,  0.0f,     -0.1f,   0.1f,  0.0f,     -0.1f, -0.05f,  0.0f,
    -0.1f,   0.1f,  0.0f,     -0.1f,  -0.05f, 0.0f,      0.1f,  0.05f,  0.0f,
     

};

GLfloat col_S[72*3]; //define S col matrix


//define T vao, vbo
GLuint vao_T;
GLuint vbo_pos_T;
GLuint vbo_col_T;

GLfloat pos_T[] = { //define T pos matrix
    //kreska
    -0.075f,-0.5f,  0.0f,     0.075f, -0.5f,  0.0f,      0.075f, 0.5f,  0.0f,
    -0.075f,-0.5f,  0.0f,    -0.075f,  0.5f,  0.0f,      0.075f, 0.5f,  0.0f,

    //gora
     0.25f,  0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,      0.25f,  0.35f, 0.0f,
    -0.25f,  0.5f,  0.0f,      0.25f,  0.35f, 0.0f,     -0.25f,  0.35f, 0.0f

};

GLfloat col_T[12*3]; //define T col matrix

//define U vao, vbo
GLuint vao_U;
GLuint vbo_pos_U;
GLuint vbo_col_U;

GLfloat pos_U[] = { //define U pos matrix
    //lewa
    -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,     -0.25f, -0.2f,  0.0f,
    -0.1f,   0.5f,  0.0f,     -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,

    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.2f,  0.0f,     -0.2f,  -0.4f,  0.0f,
    -0.1f,  -0.2f,  0.0f,     -0.2f,  -0.4f,  0.0f,     -0.05f, -0.35f, 0.0f,

    -0.2f,  -0.4f,  0.0f,     -0.05f, -0.35f, 0.0f,     -0.1f,  -0.5f,  0.0f,

    //prawa
     0.25f,  0.5f,  0.0f,      0.1f,   0.5f,  0.0f,      0.25f, -0.2f,  0.0f,
     0.1f,   0.5f,  0.0f,      0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,

     0.25f, -0.2f,  0.0f,      0.1f,  -0.2f,  0.0f,      0.2f,  -0.4f,  0.0f,
     0.1f,  -0.2f,  0.0f,      0.2f,  -0.4f,  0.0f,      0.05f, -0.35f, 0.0f,

     0.2f,  -0.4f,  0.0f,      0.05f, -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,

    //dol
    -0.05f, -0.35f, 0.0f,     -0.1f,  -0.5f,  0.0f,      0.05f, -0.35f, 0.0f,
     0.05f, -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,     -0.1f,  -0.5f,  0.0f

};

GLfloat col_U[36*3]; //define U col matrix


//define V vao, vbo
GLuint vao_V;
GLuint vbo_pos_V;
GLuint vbo_col_V;

GLfloat pos_V[] = { //define V pos matrix
    //lewa
    -0.25f,  0.5f,  0.0f,     -0.075f,-0.5f,  0.0f,      0.075f,-0.5f,  0.0f,
    -0.25f,  0.5f,  0.0f,      0.075f,-0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

    //prawa
     0.25f,  0.5f,  0.0f,      0.075f,-0.5f,  0.0f,     -0.075f,-0.5f,  0.0f,
     0.25f,  0.5f,  0.0f,     -0.075f,-0.5f,  0.0f,      0.1f,   0.5f,  0.0f

};

GLfloat col_V[12*3]; //define V col matrix


//define W vao, vbo
GLuint vao_W;
GLuint vbo_pos_W;
GLuint vbo_col_W;

GLfloat pos_W[] = { //define W pos matrix
    //lewa
    -0.25f,  0.5f,  0.0f,     -0.2f,  -0.5f,  0.0f,     -0.05f, -0.5f,  0.0f,
    -0.25f,  0.5f,  0.0f,     -0.05f, -0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,

    -0.05f, -0.5f,  0.0f,      0.0f,  -0.3f,  0.0f,     -0.07f, -0.2f,  0.0f,
     0.0f,  -0.3f,  0.0f,     -0.07f, -0.2f,  0.0f,      0.0f,   0.0f,  0.0f,
    //prawa
     0.25f,  0.5f,  0.0f,      0.2f,  -0.5f,  0.0f,      0.05f, -0.5f,  0.0f,
     0.25f,  0.5f,  0.0f,      0.05f, -0.5f,  0.0f,      0.1f,   0.5f,  0.0f,

     0.05f, -0.5f,  0.0f,      0.0f,  -0.3f,  0.0f,      0.07f, -0.2f,  0.0f,
     0.0f,  -0.3f,  0.0f,      0.07f, -0.2f,  0.0f,      0.0f,   0.0f,  0.0f

};

GLfloat col_W[24*3]; //define W col matrix

//define Z vao, vbo
GLuint vao_Z;
GLuint vbo_pos_Z;
GLuint vbo_col_Z;

GLfloat pos_Z[] = { //define Z pos matrix
    //gora
     0.25f,  0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,      0.25f,  0.35f, 0.0f,
    -0.25f,  0.5f,  0.0f,      0.25f,  0.35f, 0.0f,     -0.25f,  0.35f, 0.0f,
    //dol
     0.25f, -0.5f,  0.0f,     -0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,
    -0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,     -0.25f, -0.35f, 0.0f,

    //skos
    -0.25f, -0.35f, 0.0f,     -0.1f,  -0.35f, 0.0f,      0.1f,   0.35f, 0.0f,
    -0.1f,  -0.35f, 0.0f,      0.1f,   0.35f, 0.0f,      0.25f,  0.35f, 0.0f

};

GLfloat col_Z[18*3]; //define Z col matrix

void init_A(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_A);
    glBindVertexArray(vao_A);

    for (int i = 0; i < 24 * 3; i += 3) {
        col_A[i]    = 1.0f; //red
        col_A[i+1]  = 0.0f; //green
        col_A[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_A);
    glGenBuffers(1, &vbo_col_A);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_A); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_A), pos_A, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_A);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_A), col_A, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_B(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_B);
    glBindVertexArray(vao_B);

    for (int i = 0; i < 57 * 3; i += 3) {
        col_B[i]    = 1.0f; //red
        col_B[i+1]  = 0.0f; //green
        col_B[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_B);
    glGenBuffers(1, &vbo_col_B);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_B); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_B), pos_B, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_B);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_B), col_B, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_C(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_C);
    glBindVertexArray(vao_C);

    for (int i = 0; i < 48 * 3; i += 3) {
        col_C[i]    = 1.0f; //red
        col_C[i+1]  = 0.0f; //green
        col_C[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_C);
    glGenBuffers(1, &vbo_col_C);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_C); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_C), pos_C, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_C);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_C), col_C, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_D(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_D);
    glBindVertexArray(vao_D);

    for (int i = 0; i < 36 * 3; i += 3) {
        col_D[i]    = 1.0f; //red
        col_D[i+1]  = 0.0f; //green
        col_D[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_D);
    glGenBuffers(1, &vbo_col_D);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_D); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_D), pos_D, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_D);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_D), col_D, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_E(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_E);
    glBindVertexArray(vao_E);

    for (int i = 0; i < 24 * 3; i += 3) {
        col_E[i]    = 1.0f; //red
        col_E[i+1]  = 0.0f; //green
        col_E[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_E);
    glGenBuffers(1, &vbo_col_E);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_E); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_E), pos_E, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_E);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_E), col_E, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_G(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_G);
    glBindVertexArray(vao_G);

    for (int i = 0; i < 60 * 3; i += 3) {
        col_G[i]    = 1.0f; //red
        col_G[i+1]  = 0.0f; //green
        col_G[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_G);
    glGenBuffers(1, &vbo_col_G);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_G); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_G), pos_G, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_G);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_G), col_G, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_I(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_I);
    glBindVertexArray(vao_I);

    for (int i = 0; i < 6 * 3; i += 3) {
        col_I[i]    = 1.0f; //red
        col_I[i+1]  = 0.0f; //green
        col_I[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_I);
    glGenBuffers(1, &vbo_col_I);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_I); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_I), pos_I, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_I);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_I), col_I, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_K(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_K);
    glBindVertexArray(vao_K);

    for (int i = 0; i < 18 * 3; i += 3) {
        col_K[i]    = 1.0f; //red
        col_K[i+1]  = 0.0f; //green
        col_K[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_K);
    glGenBuffers(1, &vbo_col_K);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_K); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_K), pos_K, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_K);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_K), col_K, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_L(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_L);
    glBindVertexArray(vao_L);

    for (int i = 0; i < 12 * 3; i += 3) {
        col_L[i]    = 1.0f; //red
        col_L[i+1]  = 0.0f; //green
        col_L[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_L);
    glGenBuffers(1, &vbo_col_L);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_L); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_L), pos_L, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_L);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_L), col_L, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_N(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_N);
    glBindVertexArray(vao_N);

    for (int i = 0; i < 18 * 3; i += 3) {
        col_N[i]    = 1.0f; //red
        col_N[i+1]  = 0.0f; //green
        col_N[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_N);
    glGenBuffers(1, &vbo_col_N);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_N); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_N), pos_N, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_N);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_N), col_N, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_O(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_O);
    glBindVertexArray(vao_O);

    for (int i = 0; i < 54 * 3; i += 3) {
        col_O[i]    = 1.0f; //red
        col_O[i+1]  = 0.0f; //green
        col_O[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_O);
    glGenBuffers(1, &vbo_col_O);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_O); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_O), pos_O, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_O);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_O), col_O, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_P(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_P);
    glBindVertexArray(vao_P);

    for (int i = 0; i < 33 * 3; i += 3) {
        col_P[i]    = 1.0f; //red
        col_P[i+1]  = 0.0f; //green
        col_P[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_P);
    glGenBuffers(1, &vbo_col_P);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_P); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_P), pos_P, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_P);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_P), col_P, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_R(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_R);
    glBindVertexArray(vao_R);

    for (int i = 0; i < 39 * 3; i += 3) {
        col_R[i]    = 1.0f; //red
        col_R[i+1]  = 0.0f; //green
        col_R[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_R);
    glGenBuffers(1, &vbo_col_R);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_R); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_R), pos_R, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_R);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_R), col_R, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}   

void init_S(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_S);
    glBindVertexArray(vao_S);

    for (int i = 0; i < 72 * 3; i += 3) {
        col_S[i]    = 1.0f; //red
        col_S[i+1]  = 0.0f; //green
        col_S[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_S);
    glGenBuffers(1, &vbo_col_S);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_S); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_S), pos_S, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_S);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_S), col_S, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}   

void init_T(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_T);
    glBindVertexArray(vao_T);

    for (int i = 0; i < 12 * 3; i += 3) {
        col_T[i]    = 1.0f; //red
        col_T[i+1]  = 0.0f; //green
        col_T[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_T);
    glGenBuffers(1, &vbo_col_T);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_T); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_T), pos_T, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_T);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_T), col_T, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_U(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_U);
    glBindVertexArray(vao_U);

    for (int i = 0; i < 36 * 3; i += 3) {
        col_U[i]    = 1.0f; //red
        col_U[i+1]  = 0.0f; //green
        col_U[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_U);
    glGenBuffers(1, &vbo_col_U);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_U); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_U), pos_U, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_U);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_U), col_U, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_V(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_V);
    glBindVertexArray(vao_V);

    for (int i = 0; i < 12 * 3; i += 3) {
        col_V[i]    = 1.0f; //red
        col_V[i+1]  = 0.0f; //green
        col_V[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_V);
    glGenBuffers(1, &vbo_col_V);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_V); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_V), pos_V, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_V);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_V), col_V, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_W(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_W);
    glBindVertexArray(vao_W);

    for (int i = 0; i < 24 * 3; i += 3) {
        col_W[i]    = 1.0f; //red
        col_W[i+1]  = 0.0f; //green
        col_W[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_W);
    glGenBuffers(1, &vbo_col_W);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_W); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_W), pos_W, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_W);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_W), col_W, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_Z(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_Z);
    glBindVertexArray(vao_Z);

    for (int i = 0; i < 18 * 3; i += 3) {
        col_Z[i]    = 1.0f; //red
        col_Z[i+1]  = 0.0f; //green
        col_Z[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_Z);
    glGenBuffers(1, &vbo_col_Z);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_Z); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_Z), pos_Z, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_Z);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_Z), col_Z, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void initLetters(GLuint shaderProgram) {
    init_A(shaderProgram);
    init_B(shaderProgram);
    init_C(shaderProgram);
    init_D(shaderProgram);
    init_E(shaderProgram);
    init_G(shaderProgram);
    init_I(shaderProgram);
    init_K(shaderProgram);
    init_L(shaderProgram);
    init_N(shaderProgram);
    init_O(shaderProgram);
    init_P(shaderProgram);
    init_R(shaderProgram);
    init_S(shaderProgram);
    init_T(shaderProgram);
    init_U(shaderProgram);
    init_V(shaderProgram);
    init_W(shaderProgram);
    init_Z(shaderProgram);
}

void drawLetter(char letter, glm::vec3 position, float scale, GLuint shaderProgram, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), position);
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
    glm::mat4 modelMatrix = translationMatrix * scaleMatrix;
    glm::mat4 transformMatrix = projectionMatrix * viewMatrix * modelMatrix;

    GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");
    glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));

    switch (letter){
    case 'A':
    glBindVertexArray(vao_A);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    break;
    case 'B':
    glBindVertexArray(vao_B);
    glDrawArrays(GL_TRIANGLES, 0, 57);
    break;
    case 'C':
    glBindVertexArray(vao_C);
    glDrawArrays(GL_TRIANGLES, 0, 48);
    break;
    case 'D':
    glBindVertexArray(vao_D);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    break;
    case 'E':
    glBindVertexArray(vao_E);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    break;
    case 'G':
    glBindVertexArray(vao_G);
    glDrawArrays(GL_TRIANGLES, 0, 60);
    break;
    case 'I':
    glBindVertexArray(vao_I);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    break;
    case 'K':
    glBindVertexArray(vao_K);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    break;
    case 'L':
    glBindVertexArray(vao_L);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    break;
    case 'N':
    glBindVertexArray(vao_N);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    break;
    case 'O':
    glBindVertexArray(vao_O);
    glDrawArrays(GL_TRIANGLES, 0, 54);
    break;
    case 'P':
    glBindVertexArray(vao_P);
    glDrawArrays(GL_TRIANGLES, 0, 33);
    break;
    case 'R':
    glBindVertexArray(vao_R);
    glDrawArrays(GL_TRIANGLES, 0, 39);
    break;
    case 'S':
    glBindVertexArray(vao_S);
    glDrawArrays(GL_TRIANGLES, 0, 72);
    break;
    case 'T':
    glBindVertexArray(vao_T);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    break;
    case 'U':
    glBindVertexArray(vao_U);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    break;
    case 'V':
    glBindVertexArray(vao_V);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    break;
    case 'W':
    glBindVertexArray(vao_W);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    break;
    case 'Z':
    glBindVertexArray(vao_Z);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    break;
    }
}

void drawText(const char* text, glm::vec3 startPosition, float scale, GLuint shaderProgram, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
    float offset = 0.0f;

    for (int i = 0; text[i] != '\0'; i++) {
        glm::vec3 currentPos = glm::vec3(startPosition.x + offset, startPosition.y, startPosition.z);
        drawLetter(text[i], currentPos, scale, shaderProgram, projectionMatrix, viewMatrix);
        offset += (0.6f * scale);
    }
}

void deleteLeters() {
    glDeleteBuffers(1, &vbo_pos_A);
    glDeleteBuffers(1, &vbo_col_A);
    glDeleteVertexArrays(1, &vao_A);
}