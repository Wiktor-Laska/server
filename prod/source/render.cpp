#define GL_GLEXT_PROTOTYPES

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include "render.h"
#include "../glm/glm.hpp"
#include "../glm/gtc/matrix_transform.hpp"
#include "../glm/gtc/type_ptr.hpp"

#include "letters.h"

//TODO:
//implement scenes
//implement buttons

GLuint vbo[4];		//identyfikatory buforow wierzcholkow
GLuint vao[2];		//identyfikatory tablic wierzcholkow
GLuint ebo;		//identyfikator bufora elementow

GLuint shaderProgram;
GLint vertexShader;	//identyfikator shadera wierzcholkow
GLint fragmentShader;   //identyfikator shadera fragmentow
GLint posAttrib, colAttrib;	//
static GLint colorMulUniformLocation = -1;

glm::mat4 viewMatrix = glm::mat4();
glm::mat4 projectionMatrix = glm::mat4(); //marzerz widoku i rzutowania
GLfloat fi = 0;
bool lobby = true;
bool game = false;
bool results = false;
std::string ip = "";
std::string ip_text = "IP ";

// --- WSPÓŁDZIELONY STAN GRY ---
int stan_gry = 1;         // 1-Lobby, 2-Gra, 3-Koniec
int num_players = 0;
int runda_trwa = 0;
char runda_lvl = '1';
char punkty[4] = {0};
char kolory_tekst[9] = {0}; // Pierwsze 9 bajtów (np. jakie słowo) 49(1)->
char kolory_tusz[9] = {0};  // Drugie 9 bajtów (np. jakim kolorem pomalowane)

char cel_tekst = 0;         // Pierwszy pojedynczy bajt (cel do znalezienia)
char cel_tusz = 0;          // Drugi pojedynczy bajt (wskazówka)

char zdarzenia[4] = {0};
char winner = ' ';
char win_val = 0;


std::string nazwa_text(char c){
  switch(c)
{
  case '1':
    return "WHITE";
  break;
  case '2':
    return "YELLOW";
  break;
  case '3':
    return "GREEN";
  break;
  case '4':
    return "BLUE";
  break;
  case '5':
    return "PINK";
  break;
  case '6':
    return "BROWN";
  break;
  case '7':
    return "RED";
  break;
  case '8':
    return "ORANGE";
  break;
  case '0':
    return "GRAY";
  break;
  default:
  return "";
}

}


glm::vec3 tusz_text(char c){
    switch(c)
{
  case '1':
    return glm::vec3(1.0f, 1.0f, 1.0f);
  break;
  case '2':
    return glm::vec3(1.0f, 1.0f, 0.0f);
  break;
  case '3':
    return glm::vec3(0.0f, 1.0f, 0.0f);
  break;
  case '4':
    return glm::vec3(0.0f, 0.0f, 1.0f);
  break;
  case '5':
    return glm::vec3(1.0f, 0.0f, 1.0f);
  break;
  case '6':
    return glm::vec3(0.7f, 0.3f, 0.0f);
  break;
  case '7':
    return glm::vec3(1.0f, 0.0f, 0.0f);
  break;
  case '8':
    return glm::vec3(1.0f, 0.7f, 0.0f);
  break;
  case '0':
    return glm::vec3(0.2f, 0.2f, 0.2f);
  break;
  default:
  return glm::vec3(0.0f, 0.0f, 0.0f);
}
}


//-------------Atrybuty wierzcholkow------------------------------------------

	GLfloat ver_triangle[] = {	//wspolrzedne wierzcholkow trojkata
		 0.0f,  1.0f, 0.0,
		 1.0f,  0.0f, 0.0,
		-1.0f,  0.0f, 0.0
	};

	GLfloat col_triangle[] = {	//kolory wierzcholkow trojkata
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	GLfloat ver_rectangle[] = {	//wspolrzedne wierzcholkow prostokata
		-1.0f, -0.2f, 0.0f,
		 1.0f, -0.2f, 0.0f,
		-1.0f, -0.7f, 0.0f,
		 1.0f, -0.7f, 0.0f
	};

	GLfloat col_rectangle[] = {	//kolory wierzcholkow prostokata
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f
	};

	GLuint elements[] = { //prostokat skladamy z dwoch trojkatow
		0, 1, 2,		  //indeksy wierzcholkow dla pierwszego trojkata
		1, 2, 3			  //indeksy wierzcholkow dla drugiego trojkata
	};


//----------------------------kod shadera wierzcholkow-----------------------------------------

const GLchar* vShader_string =
{
  "#version 130\n"\

  "in vec3 position;\n"\
  "in vec3 color;\n"\
  "out vec3 Color;\n"\
  "uniform mat4 transformMatrix;\n"\
  "void main(void)\n"\
  "{\n"\
  "  gl_Position = transformMatrix * vec4(position, 1.0);\n"\
  "  Color = color;\n"\
  "}\n"
};

//----------------------------kod shadera fragmentow-------------------------------------------
const GLchar* fShader_string =
{
  "#version 130\n"\
  "in  vec3 Color;\n"\
  "uniform vec3 colorMul;\n"\
  "out vec4 outColor;\n"\

  "void main(void)\n"\
  "{\n"\
  "  outColor = vec4(Color * colorMul, 1.0);\n"\
  "}\n"
};


//------------------------------------------------zmiana rozmiaru okna---------------------------

void resizeGLScene(unsigned int width, unsigned int height)
{
    if (height == 0) height = 1; // zabezpiecznie dla okna o zerowej wysokosci
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 1.0f, 500.0f);
    glMatrixMode(GL_MODELVIEW);
}


//----------------------------------tworzenie, wczytanie, kompilacja shaderow-------------------------

int initShaders(void)
{
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vShader_string, NULL);
    glCompileShader(vertexShader);
    
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
      std::cout << "Kompilacja shadera wierzcholkow powiodla sie!\n";
    else
    {
      std::cout << "Kompilacja shadera wierzcholkow NIE powiodla sie!\n";
      return 0;
     }
     
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fShader_string, NULL); 
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_TRUE)
      std::cout << "Kompilacja shadera fragmentow powiodla sie!\n";
    else
    {
      std::cout << "Kompilacja shadera fragmentow NIE powiodla sie!\n";
      return 0;
    }

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    //glBindFragDataLocation(shaderProgram, 0, "outColor"); 

    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
    return 1;
}



//--------------------------------------------funkcja inicjujaca-------------------------------------
int initGL(void)
{
  
    if(initShaders())
    {   

        glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 
	glGenVertexArrays(2, vao); //przypisanie do vao identyfikatorow tablic
	glGenBuffers(4, vbo);	   //przypisanie do vbo identyfikatorow buforow
	glGenBuffers(1, &ebo);

	posAttrib = glGetAttribLocation(shaderProgram, "position"); //pobranie indeksu tablicy atrybutow wierzcholkow okreslajacych polozenie
        glEnableVertexAttribArray(posAttrib);
	colAttrib = glGetAttribLocation(shaderProgram, "color");    //pobranie indeksu tablicy atrybutow wierzcholkow okreslajacych kolor
        glEnableVertexAttribArray(colAttrib);
        colorMulUniformLocation = glGetUniformLocation(shaderProgram, "colorMul");
        if (colorMulUniformLocation >= 0) {
            glUniform3f(colorMulUniformLocation, 1.0f, 1.0f, 1.0f);
        }
	
	glBindVertexArray(vao[0]);					//wybor tablicy
		
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]); 							//powiazanie bufora z odpowiednim obiektem (wybor bufora) 
	glBufferData(GL_ARRAY_BUFFER, sizeof(ver_triangle), ver_triangle, GL_STATIC_DRAW); 	//skopiowanie danych do pamieci aktywnego bufora
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);				//okreslenie organizacji danych w tablicy wierzcholkow
	glEnableVertexAttribArray(posAttrib);							//wlaczenie tablicy
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_triangle), col_triangle, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);
	
	glBindVertexArray(vao[1]);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ver_rectangle), ver_rectangle, GL_STATIC_DRAW);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(col_rectangle), col_rectangle, GL_STATIC_DRAW);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(colAttrib);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);
        
	//macierz widoku (okresla polozenie kamery i kierunek w ktorym jest skierowana) 
	viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
	//macierz rzutowania perspektywicznego
	projectionMatrix = glm::perspective(glm::radians(45.0f), 1.0f, 1.0f, 20.0f);		
  initLetters(shaderProgram);

 	return 1;
    }
    else
	return 0;
}

//------------------------------------------renderowanie sceny-------------------------------------

int drawGLScene(int counter)
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    if (colorMulUniformLocation >= 0) {
        glUniform3f(colorMulUniformLocation, 1.0f, 1.0f, 1.0f);
    }
    
    glm::mat4 translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));  		//macierz przesuniecia o zadany wektor
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(), glm::radians(fi), glm::vec3(0.0f, 1.0f, 0.0f)); //macierz obrotu o dany kat wokol wektora
    glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		
    glm::mat4 transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix; //wygenerowanie macierzy uwzgledniajacej wszystkie transformacje


    GLint transformMatrixUniformLocation = glGetUniformLocation(shaderProgram, "transformMatrix");  //pobranie polozenia macierzy bedacej zmienna jednorodna shadera
    glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix)); //zapisanie macierzy bedacej zmienna jednorodna shadera wierzcholkow
    
    /*
    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, 3); //rysowanie trojkata
    */

    
    //fi += 0.5;

    //lobby = true;

    if (stan_gry == 4){      // result scene
      std::string string_winner_name = "WINNER " + winner; 
      std::string string_winner_val = "POINTS " + std::to_string(int(win_val));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -0.8f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      drawText("RESULTS", glm::vec3(-1.2f, 1.5f, 0.0f), 0.4f, shaderProgram, projectionMatrix, viewMatrix);
      drawText(string_winner_name, glm::vec3(-1.5f, 1.0f, 0.0f), 0.3f, shaderProgram, projectionMatrix, viewMatrix);
      drawText(string_winner_val, glm::vec3(-1.5f, 0.5f, 0.0f), 0.3f, shaderProgram, projectionMatrix, viewMatrix);
      drawText("JOIN AGAIN", glm::vec3(-0.8f, -0.45f, 0.0f), 0.3f, shaderProgram, projectionMatrix, viewMatrix);
      drawText("MAIN MENU", glm::vec3(-0.8f, -1.25f, 0.0f), 0.3f, shaderProgram, projectionMatrix, viewMatrix);
    } else if (stan_gry == 3){ // lobby scene
      //5
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, -0.1f, 0.0f));
      scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 1.0f, 1.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix; 
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix)); 
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      //2
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.5f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      //4
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.1f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata

      //8
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(-1.1f, -0.1f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix; 
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix)); 
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      //1
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(-1.1f, 0.5f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      //6
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(-1.1f, 1.1f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata

      //9
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(1.1f, -0.1f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix; 
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix)); 
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      //3
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(1.1f, 0.5f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      //7
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(1.1f, 1.1f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata

      //upper
      scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f, 1.9f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata

      //lower
      scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
      translationMatrix = glm::translate(glm::mat4(), glm::vec3(0.0f,-0.9f, 0.0f));
      transformMatrix = projectionMatrix * viewMatrix * translationMatrix * rotationMatrix * scaleMatrix;
      glUniformMatrix4fv(transformMatrixUniformLocation, 1, GL_FALSE, glm::value_ptr(transformMatrix));
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata

      if(runda_trwa){
      //1
      drawText(nazwa_text(kolory_tekst[0]), glm::vec3(-1.5f, 0.05f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[0]));
      //2
      drawText(nazwa_text(kolory_tekst[1]), glm::vec3(-0.4f, 0.05f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[1]));
      //3
      drawText(nazwa_text(kolory_tekst[2]), glm::vec3(0.7f, 0.05f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[2]));
      //4
      drawText(nazwa_text(kolory_tekst[3]), glm::vec3(-0.4f, 0.65f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[3]));
      //5
      drawText(nazwa_text(kolory_tekst[4]), glm::vec3(-0.4f, -0.55f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[4]));
      //6
      drawText(nazwa_text(kolory_tekst[5]), glm::vec3(-1.5f, 0.65f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[5]));
      //7
      drawText(nazwa_text(kolory_tekst[6]), glm::vec3(0.7f, 0.65f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[6]));
      //8
      drawText(nazwa_text(kolory_tekst[7]), glm::vec3(-1.5f, -0.55f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[7]));
      //9
      drawText(nazwa_text(kolory_tekst[8]), glm::vec3(0.7f, -0.55f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix, tusz_text(kolory_tusz[8]));
      //change to received text
      std::string key_text = nazwa_text(cel_tekst);
      float offset = key_text.length()*-0.12f;
      //change to recived colour
      glm::vec3 key_color = tusz_text(cel_tusz);
      //top
      drawText(key_text, glm::vec3(offset+0.12f, 1.45f, 0.0f), 0.4f, shaderProgram, projectionMatrix, viewMatrix, key_color);
      //bot
      drawText(key_text, glm::vec3(offset+0.12f, -1.35f, 0.0f), 0.4f, shaderProgram, projectionMatrix, viewMatrix, key_color);
      }


    } else if (stan_gry == 2) { // game scene
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      drawText("WAITING", glm::vec3(-1.2f, 1.5f, 0.0f), 0.4f, shaderProgram, projectionMatrix, viewMatrix);
      drawText("READY", glm::vec3(-0.7f, -0.45f, 0.0f), 0.4f, shaderProgram, projectionMatrix, viewMatrix);
    } else {           // main menu scene
      glBindVertexArray(vao[1]);
      glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0); //rysowanie prostokata
      drawText("STROOPVIVAL", glm::vec3(-1.2f, 1.5f, 0.0f), 0.4f, shaderProgram, projectionMatrix, viewMatrix);
      drawText(ip_text, glm::vec3(-1.3f, 0.1f, 0.0f), 0.25f, shaderProgram, projectionMatrix, viewMatrix);
      drawText("CONNECT", glm::vec3(-0.7f, -0.45f, 0.0f), 0.4f, shaderProgram, projectionMatrix, viewMatrix, glm::vec3(0.0, 0.0, 0.0));
    }
    glFlush();

    return 1;    
}

//----------------------------------------------------porzadki--------------------------------------

void deleteAll()
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(fragmentShader);
    glDeleteShader(vertexShader);

    glDeleteBuffers(4, vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteVertexArrays(2, vao);
    deleteLeters();
}

