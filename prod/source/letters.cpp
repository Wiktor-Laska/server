#include "letters.h"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"
#include <iostream>
#include <string>


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

GLfloat col_I[6*3]; //define I col matrix


//define J vao, vbo
GLuint vao_J;
GLuint vbo_pos_J;
GLuint vbo_col_J;

GLfloat pos_J[] = { //define J pos matrix
    //gora
    -0.25f,  0.35f, 0.0f,      0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,
    -0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,

    //prawa
     0.1f,  -0.5f,  0.0f,      0.25f, -0.5f,  0.0f,      0.25f,  0.5f,  0.0f,
     0.1f,  -0.5f,  0.0f,      0.25f,  0.5f,  0.0f,      0.1f,   0.5f,  0.0f,

    //dol
    -0.15f, -0.5f,  0.0f,      0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,
    -0.15f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,     -0.15f, -0.35f, 0.0f,

    //lewa
    -0.25f, -0.35f, 0.0f,     -0.1f,  -0.35f, 0.0f,     -0.1f,  -0.15f, 0.0f,
    -0.25f, -0.35f, 0.0f,     -0.1f,  -0.15f, 0.0f,     -0.25f, -0.15f, 0.0f
};

GLfloat col_J[24*3]; //define J col matrix

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


//define Y vao, vbo
GLuint vao_Y;
GLuint vbo_pos_Y;
GLuint vbo_col_Y;

GLfloat pos_Y[] = { //define Y pos matrix
    //lewa
    -0.25f,  0.5f,  0.0f,     -0.1f,   0.5f,  0.0f,      0.0f,   0.1f,  0.0f,
    -0.25f,  0.5f,  0.0f,      0.0f,   0.1f,  0.0f,     -0.05f, -0.3f,  0.0f,

    //prawa
     0.25f,  0.5f,  0.0f,      0.1f,   0.5f,  0.0f,      0.0f,   0.1f,  0.0f,
     0.25f,  0.5f,  0.0f,      0.0f,   0.1f,  0.0f,      0.05f, -0.3f,  0.0f,

    //kreska
    -0.075f, 0.1f,  0.0f,      0.075f, 0.1f,  0.0f,      0.075f,-0.5f,  0.0f,
    -0.075f, 0.1f,  0.0f,      0.075f,-0.5f,  0.0f,     -0.075f,-0.5f,  0.0f
};

GLfloat col_Y[18*3]; //define Y col matrix


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


//define . vao, vbo
GLuint vao_DOT;
GLuint vbo_pos_DOT;
GLuint vbo_col_DOT;

GLfloat pos_DOT[] = { //define . pos matrix
    -0.05f, -0.5f,  0.0f,      0.05f, -0.5f,  0.0f,      0.05f, -0.4f,  0.0f,
    -0.05f, -0.5f,  0.0f,      0.05f, -0.4f,  0.0f,     -0.05f, -0.4f,  0.0f
};

GLfloat col_DOT[6*3]; //define . col matrix
 

//define 0 vao, vbo
GLuint vao_0;
GLuint vbo_pos_0;
GLuint vbo_col_0;

GLfloat pos_0[] = { //define 0 pos matrix
     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.1f,   0.5f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.1f,   0.5f,  0.0f,     -0.0f,   0.35f, 0.0f,

     0.1f,   0.5f,  0.0f,     -0.0f,   0.35f, 0.0f,     -0.1f,   0.5f,  0.0f,
    -0.0f,   0.35f, 0.0f,     -0.1f,   0.5f,  0.0f,     -0.1f,   0.3f,  0.0f,

    -0.1f,   0.5f,  0.0f,     -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,
    -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,     -0.1f,  -0.3f,  0.0f,

    -0.25f,  0.3f,  0.0f,     -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,

     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.1f,  -0.3f,  0.0f,
     0.25f,  0.3f,  0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,

    -0.1f,  -0.2f,  0.0f,     -0.25f, -0.2f,  0.0f,     -0.1f,  -0.3f,  0.0f,
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,

    -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,
    -0.1f,  -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,

    -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,
     0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,

     0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,

    -0.1f,  -0.2f,  0.0f,     -0.1f,  -0.15f, 0.0f,      0.1f,   0.15f, 0.0f,
    -0.1f,  -0.15f, 0.0f,      0.1f,   0.15f, 0.0f,      0.1f,   0.2f,  0.0f
};

GLfloat col_0[54*3]; //define 0 col matrix


//define 1 vao, vbo
GLuint vao_1;
GLuint vbo_pos_1;
GLuint vbo_col_1;

GLfloat pos_1[] = { //define 1 pos matrix
    -0.2f,   0.15f, 0.0f,     -0.2f,   0.3f,  0.0f,      0.1f,   0.35f, 0.0f,
    -0.2f,   0.3f,  0.0f,      0.1f,   0.35f, 0.0f,      0.1f,   0.5f,  0.0f,

     0.1f,   0.5f,  0.0f,      0.1f,  -0.5f,  0.0f,      0.25f,  0.5f,  0.0f,
     0.1f,  -0.5f,  0.0f,      0.25f,  0.5f,  0.0f,      0.25f, -0.5f,  0.0f
};

GLfloat col_1[12*3]; //define 1 col matrix


//define 2 vao, vbo
GLuint vao_2;
GLuint vbo_pos_2;
GLuint vbo_col_2;

GLfloat pos_2[] = { //define 2 pos matrix
    -0.1f,   0.2f,  0.0f,     -0.25f,  0.2f,  0.0f,     -0.1f,   0.3f,  0.0f,
    -0.25f,  0.2f,  0.0f,     -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,

    -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.1f,   0.3f,  0.0f,     -0.1f,   0.5f,  0.0f,      0.0f,   0.35f, 0.0f,

    -0.1f,   0.5f,  0.0f,      0.0f,   0.35f, 0.0f,      0.1f,   0.5f,  0.0f,
     0.0f,   0.35f, 0.0f,      0.1f,   0.5f,  0.0f,      0.1f,   0.3f,  0.0f,

     0.1f,   0.5f,  0.0f,      0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.1f,   0.1f,  0.0f,

     0.25f,  0.3f,  0.0f,      0.1f,   0.1f,  0.0f,      0.25f,  0.1f,  0.0f,
     0.1f,   0.1f,  0.0f,      0.25f,  0.1f,  0.0f,     -0.1f,  -0.35f, 0.0f,

     0.1f,   0.1f,  0.0f,     -0.1f,  -0.35f, 0.0f,     -0.25f, -0.35f, 0.0f,
    -0.25f, -0.35f, 0.0f,     -0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,
    -0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,      0.25f, -0.5f,  0.0f

};

GLfloat col_2[39*3]; //define 2 col matrix


//define 3 vao, vbo
GLuint vao_3;
GLuint vbo_pos_3;
GLuint vbo_col_3;

GLfloat pos_3[] = { //define 3 pos matrix
    -0.1f,   0.2f,  0.0f,     -0.25f,  0.2f,  0.0f,     -0.1f,   0.3f,  0.0f,
    -0.25f,  0.2f,  0.0f,     -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,

    -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,     -0.1f,   0.5f,  0.0f,
    -0.1f,   0.3f,  0.0f,     -0.1f,   0.5f,  0.0f,      0.0f,   0.35f, 0.0f,

    -0.1f,   0.5f,  0.0f,      0.0f,   0.35f, 0.0f,      0.1f,   0.5f,  0.0f,
     0.0f,   0.35f, 0.0f,      0.1f,   0.5f,  0.0f,      0.1f,   0.3f,  0.0f,

     0.1f,   0.5f,  0.0f,      0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.1f,  -0.3f,  0.0f,

     0.25f,  0.3f,  0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,


    -0.05f,  0.1f,  0.0f,      0.1f,   0.1f,  0.0f,     -0.05f, -0.1f,  0.0f,
     0.1f,   0.1f,  0.0f,     -0.05f, -0.1f,  0.0f,      0.1f,  -0.1f,  0.0f,


    -0.1f,  -0.2f,  0.0f,     -0.25f, -0.2f,  0.0f,     -0.1f,  -0.3f,  0.0f,
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,

    -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,
    -0.1f,  -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,

    -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,
     0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,

     0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f

};

GLfloat col_3[54*3]; //define 3 col matrix


//define 4 vao, vbo
GLuint vao_4;
GLuint vbo_pos_4;
GLuint vbo_col_4;

GLfloat pos_4[] = { //define 4 pos matrix
     0.15f, -0.5f,  0.0f,      0.0f,  -0.5f,  0.0f,      0.15f,  0.5f,  0.0f,
     0.0f,  -0.5f,  0.0f,      0.15f,  0.5f,  0.0f,      0.0f,   0.5f,  0.0f,

     0.15f,  0.5f,  0.0f,      0.0f,   0.5f,  0.0f,     -0.1f,  -0.05f, 0.0f,
     0.0f,   0.5f,  0.0f,     -0.1f,  -0.05f, 0.0f,     -0.25f, -0.05f, 0.0f,

    -0.25f, -0.2f,  0.0f,     -0.25f, -0.05f, 0.0f,      0.25f, -0.2f,  0.0f,
    -0.25f, -0.05f, 0.0f,      0.25f, -0.2f,  0.0f,      0.25f, -0.05f, 0.0f
};

GLfloat col_4[18*3]; //define 4 col matrix


//define 5 vao, vbo
GLuint vao_5;
GLuint vbo_pos_5;
GLuint vbo_col_5;

GLfloat pos_5[] = { //define 5 pos matrix
    -0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,      0.25f,  0.35f, 0.0f,
    -0.25f,  0.5f,  0.0f,     -0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,

    -0.25f,  0.0f,  0.0f,     -0.1f,   0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,
    -0.1f,   0.0f,  0.0f,     -0.25f,  0.0f,  0.0f,     -0.1f,   0.5f,  0.0f,

     0.1f,  -0.1f,  0.0f,     -0.1f,   0.15f, 0.0f,     -0.1f,   0.0f,  0.0f,
     0.25f,  0.0f,  0.0f,      0.1f,  -0.1f,  0.0f,     -0.1f,   0.15f, 0.0f,
 
     0.1f,  -0.3f,  0.0f,      0.25f,  0.0f,  0.0f,      0.1f,  -0.1f,  0.0f,
     0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,      0.25f,  0.0f,  0.0f,

    -0.1f,  -0.2f,  0.0f,     -0.25f, -0.2f,  0.0f,     -0.1f,  -0.3f,  0.0f,
    -0.25f, -0.2f,  0.0f,     -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,

    -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,
    -0.1f,  -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,

    -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,
     0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,

     0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f
};

GLfloat col_5[45*3]; //define 5 col matrix


//define 6 vao, vbo
GLuint vao_6;
GLuint vbo_pos_6;
GLuint vbo_col_6;

GLfloat pos_6[] = { //define 6 pos matrix
     0.1f,   0.2f,  0.0f,      0.25f,  0.2f,  0.0f,      0.1f,   0.3f,  0.0f,
     0.25f,  0.2f,  0.0f,      0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,

     0.1f,   0.3f,  0.0f,      0.25f,  0.3f,  0.0f,      0.1f,   0.5f,  0.0f,
     0.1f,   0.3f,  0.0f,      0.1f,   0.5f,  0.0f,     -0.0f,   0.35f, 0.0f,

     0.1f,   0.5f,  0.0f,     -0.0f,   0.35f, 0.0f,     -0.1f,   0.5f,  0.0f,
    -0.0f,   0.35f, 0.0f,     -0.1f,   0.5f,  0.0f,     -0.1f,   0.3f,  0.0f,

    -0.1f,   0.5f,  0.0f,     -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,
    -0.1f,   0.3f,  0.0f,     -0.25f,  0.3f,  0.0f,     -0.1f,  -0.3f,  0.0f,

    -0.25f,  0.3f,  0.0f,     -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,
    -0.1f,  -0.3f,  0.0f,     -0.25f, -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,

    -0.1f,  -0.3f,  0.0f,     -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,
    -0.1f,  -0.5f,  0.0f,      0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,

     0.0f,  -0.35f, 0.0f,      0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,
     0.1f,  -0.5f,  0.0f,      0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,

     0.1f,  -0.3f,  0.0f,      0.25f, -0.3f,  0.0f,      0.25f, -0.1f,  0.0f, 
     0.1f,  -0.3f,  0.0f,      0.25f, -0.1f,  0.0f,      0.1f,  -0.1f,  0.0f, 

     0.25f, -0.1f,  0.0f,      0.1f,  -0.1f,  0.0f,      0.1f,   0.05f, 0.0f,
     0.1f,  -0.1f,  0.0f,      0.1f,   0.05f, 0.0f,      0.0f,  -0.05f, 0.0f,

     0.1f,   0.05f, 0.0f,      0.0f,  -0.05f, 0.0f,      0.0f,   0.1f,  0.0f,
     0.0f,  -0.05f, 0.0f,      0.0f,   0.1f,  0.0f,     -0.1f,   0.05f, 0.0f,

     0.0f,  -0.05f, 0.0f,     -0.1f,   0.05f, 0.0f,     -0.1f,  -0.1f,  0.0f
};

GLfloat col_6[63*3]; //define 6 col matrix


//define 7 vao, vbo
GLuint vao_7;
GLuint vbo_pos_7;
GLuint vbo_col_7;

GLfloat pos_7[] = { //define 7 pos matrix
    -0.25f,  0.5f,  0.0f,      0.25f,  0.5f,  0.0f,     -0.25f,  0.35f, 0.0f,
     0.25f,  0.5f,  0.0f,     -0.25f,  0.35f, 0.0f,      0.25f,  0.35f, 0.0f,

     0.25f,  0.35f, 0.0f,      0.1f,   0.35f, 0.0f,      0.0f,  -0.5f,  0.0f,
     0.1f,   0.35f, 0.0f,      0.0f,  -0.5f,  0.0f,     -0.15f, -0.5f,  0.0f
};

GLfloat col_7[12*3]; //define 7 col matrix


//define 8 vao, vbo
GLuint vao_8;
GLuint vbo_pos_8;
GLuint vbo_col_8;

GLfloat pos_8[] = { //define 8 pos matrix
    -0.25f,  0.35f, 0.0f,      0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,
    -0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,

    -0.25f, -0.05f, 0.0f,      0.25f, -0.05f, 0.0f,      0.25f,  0.05f, 0.0f,
    -0.25f, -0.05f, 0.0f,      0.25f,  0.05f, 0.0f,     -0.25f,  0.05f, 0.0f,

    -0.25f, -0.5f,  0.0f,      0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,
    -0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,     -0.25f, -0.35f, 0.0f,

    -0.25f,  0.05f, 0.0f,     -0.1f,   0.05f, 0.0f,     -0.1f,   0.35f, 0.0f,
    -0.25f,  0.05f, 0.0f,     -0.1f,   0.35f, 0.0f,     -0.25f,  0.35f, 0.0f,

    -0.25f, -0.35f, 0.0f,     -0.1f,  -0.35f, 0.0f,     -0.1f,  -0.05f, 0.0f,
    -0.25f, -0.35f, 0.0f,     -0.1f,  -0.05f, 0.0f,     -0.25f, -0.05f, 0.0f,

     0.1f,   0.05f, 0.0f,      0.25f,  0.05f, 0.0f,      0.25f,  0.35f, 0.0f,
     0.1f,   0.05f, 0.0f,      0.25f,  0.35f, 0.0f,      0.1f,   0.35f, 0.0f,

     0.1f,  -0.35f, 0.0f,      0.25f, -0.35f, 0.0f,      0.25f, -0.05f, 0.0f,
     0.1f,  -0.35f, 0.0f,      0.25f, -0.05f, 0.0f,      0.1f,  -0.05f, 0.0f
};

GLfloat col_8[42*3]; //define 8 col matrix


//define 9 vao, vbo
GLuint vao_9;
GLuint vbo_pos_9;
GLuint vbo_col_9;

GLfloat pos_9[] = { //define 9 pos matrix
    -0.25f,  0.35f, 0.0f,      0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,
    -0.25f,  0.35f, 0.0f,      0.25f,  0.5f,  0.0f,     -0.25f,  0.5f,  0.0f,

    -0.25f, -0.05f, 0.0f,      0.25f, -0.05f, 0.0f,      0.25f,  0.05f, 0.0f,
    -0.25f, -0.05f, 0.0f,      0.25f,  0.05f, 0.0f,     -0.25f,  0.05f, 0.0f,

    -0.25f, -0.5f,  0.0f,      0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,
    -0.25f, -0.5f,  0.0f,      0.25f, -0.35f, 0.0f,     -0.25f, -0.35f, 0.0f,

    -0.25f,  0.05f, 0.0f,     -0.1f,   0.05f, 0.0f,     -0.1f,   0.35f, 0.0f,
    -0.25f,  0.05f, 0.0f,     -0.1f,   0.35f, 0.0f,     -0.25f,  0.35f, 0.0f,

     0.1f,   0.05f, 0.0f,      0.25f,  0.05f, 0.0f,      0.25f,  0.35f, 0.0f,
     0.1f,   0.05f, 0.0f,      0.25f,  0.35f, 0.0f,      0.1f,   0.35f, 0.0f,

     0.1f,  -0.35f, 0.0f,      0.25f, -0.35f, 0.0f,      0.25f, -0.05f, 0.0f,
     0.1f,  -0.35f, 0.0f,      0.25f, -0.05f, 0.0f,      0.1f,  -0.05f, 0.0f
};

GLfloat col_9[36*3]; //define 9 col matrix



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

void init_J(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_J);
    glBindVertexArray(vao_J);

    for (int i = 0; i < 24 * 3; i += 3) {
        col_J[i]    = 1.0f; //red
        col_J[i+1]  = 0.0f; //green
        col_J[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_J);
    glGenBuffers(1, &vbo_col_J);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_J); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_J), pos_J, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_J);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_J), col_J, GL_STATIC_DRAW);
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

void init_Y(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_Y);
    glBindVertexArray(vao_Y);

    for (int i = 0; i < 18 * 3; i += 3) {
        col_Y[i]    = 1.0f; //red
        col_Y[i+1]  = 0.0f; //green
        col_Y[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_Y);
    glGenBuffers(1, &vbo_col_Y);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_Y); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_Y), pos_Y, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_Y);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_Y), col_Y, GL_STATIC_DRAW);
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

void init_DOT(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_DOT);
    glBindVertexArray(vao_DOT);

    for (int i = 0; i < 6 * 3; i += 3) {
        col_DOT[i]    = 1.0f; //red
        col_DOT[i+1]  = 0.0f; //green
        col_DOT[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_DOT);
    glGenBuffers(1, &vbo_col_DOT);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_DOT); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_DOT), pos_DOT, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_DOT);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_DOT), col_DOT, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_0(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_0);
    glBindVertexArray(vao_0);

    for (int i = 0; i < 54 * 3; i += 3) {
        col_0[i]    = 1.0f; //red
        col_0[i+1]  = 0.0f; //green
        col_0[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_0);
    glGenBuffers(1, &vbo_col_0);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_0); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_0), pos_0, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_0), col_0, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_1(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_1);
    glBindVertexArray(vao_1);

    for (int i = 0; i < 12 * 3; i += 3) {
        col_1[i]    = 1.0f; //red
        col_1[i+1]  = 0.0f; //green
        col_1[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_1);
    glGenBuffers(1, &vbo_col_1);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_1); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_1), pos_1, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_1);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_1), col_1, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_2(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_2);
    glBindVertexArray(vao_2);

    for (int i = 0; i < 39 * 3; i += 3) {
        col_2[i]    = 1.0f; //red
        col_2[i+1]  = 0.0f; //green
        col_2[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_2);
    glGenBuffers(1, &vbo_col_2);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_2); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_2), pos_2, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_2), col_2, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_3(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_3);
    glBindVertexArray(vao_3);

    for (int i = 0; i < 54 * 3; i += 3) {
        col_3[i]    = 1.0f; //red
        col_3[i+1]  = 0.0f; //green
        col_3[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_3);
    glGenBuffers(1, &vbo_col_3);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_3); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_3), pos_3, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_3), col_3, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_4(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_4);
    glBindVertexArray(vao_4);

    for (int i = 0; i < 18 * 3; i += 3) {
        col_4[i]    = 1.0f; //red
        col_4[i+1]  = 0.0f; //green
        col_4[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_4);
    glGenBuffers(1, &vbo_col_4);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_4); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_4), pos_4, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_4);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_4), col_4, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_5(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_5);
    glBindVertexArray(vao_5);

    for (int i = 0; i < 45 * 3; i += 3) {
        col_5[i]    = 1.0f; //red
        col_5[i+1]  = 0.0f; //green
        col_5[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_5);
    glGenBuffers(1, &vbo_col_5);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_5); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_5), pos_5, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_5);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_5), col_5, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_6(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_6);
    glBindVertexArray(vao_6);

    for (int i = 0; i < 63 * 3; i += 3) {
        col_6[i]    = 1.0f; //red
        col_6[i+1]  = 0.0f; //green
        col_6[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_6);
    glGenBuffers(1, &vbo_col_6);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_6); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_6), pos_6, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_6);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_6), col_6, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_7(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_7);
    glBindVertexArray(vao_7);

    for (int i = 0; i < 12 * 3; i += 3) {
        col_7[i]    = 1.0f; //red
        col_7[i+1]  = 0.0f; //green
        col_7[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_7);
    glGenBuffers(1, &vbo_col_7);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_7); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_7), pos_7, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_7);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_7), col_7, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_8(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_8);
    glBindVertexArray(vao_8);

    for (int i = 0; i < 42 * 3; i += 3) {
        col_8[i]    = 1.0f; //red
        col_8[i+1]  = 0.0f; //green
        col_8[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_8);
    glGenBuffers(1, &vbo_col_8);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_8); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_8), pos_8, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_8);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_8), col_8, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

    glBindVertexArray(0);
}

void init_9(GLuint shaderProgram) {
    glGenVertexArrays(1, &vao_9);
    glBindVertexArray(vao_9);

    for (int i = 0; i < 36 * 3; i += 3) {
        col_9[i]    = 1.0f; //red
        col_9[i+1]  = 0.0f; //green
        col_9[i+2]  = 0.0f; //blue
    }

    glGenBuffers(1, &vbo_pos_9);
    glGenBuffers(1, &vbo_col_9);
    GLint posAttrib, colAttrib;

    posAttrib = glGetAttribLocation(shaderProgram, "position"); 
	colAttrib = glGetAttribLocation(shaderProgram, "color"); 

    glBindBuffer(GL_ARRAY_BUFFER, vbo_pos_9); 							
	glBufferData(GL_ARRAY_BUFFER, sizeof(pos_9), pos_9, GL_STATIC_DRAW); 	
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				
	glEnableVertexAttribArray(posAttrib);		

    glBindBuffer(GL_ARRAY_BUFFER, vbo_col_9);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_9), col_9, GL_STATIC_DRAW);
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
    init_J(shaderProgram);
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
    init_Y(shaderProgram);
    init_Z(shaderProgram);
    init_DOT(shaderProgram);
    init_0(shaderProgram);
    init_1(shaderProgram);
    init_2(shaderProgram);
    init_3(shaderProgram);
    init_4(shaderProgram);
    init_5(shaderProgram);
    init_6(shaderProgram);
    init_7(shaderProgram);
    init_8(shaderProgram);
    init_9(shaderProgram);
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
    case 'J':
    glBindVertexArray(vao_J);
    glDrawArrays(GL_TRIANGLES, 0, 24);
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
    case 'Y':
    glBindVertexArray(vao_Y);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    break;
    case 'Z':
    glBindVertexArray(vao_Z);
    glDrawArrays(GL_TRIANGLES, 0, 24);
    break;
    case '.':
    glBindVertexArray(vao_DOT);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    break;
    case '0':
    glBindVertexArray(vao_0);
    glDrawArrays(GL_TRIANGLES, 0, 54);
    break;
    case '1':
    glBindVertexArray(vao_1);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    break;
    case '2':
    glBindVertexArray(vao_2);
    glDrawArrays(GL_TRIANGLES, 0, 39);
    break;
    case '3':
    glBindVertexArray(vao_3);
    glDrawArrays(GL_TRIANGLES, 0, 54);
    break;
    case '4':
    glBindVertexArray(vao_4);
    glDrawArrays(GL_TRIANGLES, 0, 18);
    break;
    case '5':
    glBindVertexArray(vao_5);
    glDrawArrays(GL_TRIANGLES, 0, 45);
    break;
    case '6':
    glBindVertexArray(vao_6);
    glDrawArrays(GL_TRIANGLES, 0, 63);
    break;
    case '7':
    glBindVertexArray(vao_7);
    glDrawArrays(GL_TRIANGLES, 0, 12);
    break;
    case '8':
    glBindVertexArray(vao_8);
    glDrawArrays(GL_TRIANGLES, 0, 42);
    break;
    case '9':
    glBindVertexArray(vao_9);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    break;
    }
}

void drawText(const std::string& text, glm::vec3 startPosition, float scale, GLuint shaderProgram, glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {
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
