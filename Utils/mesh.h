// classe Vertex: 
// i vertici della mesh
#ifndef MESH_H_
#define MESH_H_

#include "point3.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class Vertex
{ 
public: 
  Point3 p; // posizione
  // attributi per verice
   Vector3 n; // normale (per vertice)

  Vertex(float x, float y,float z){p= Point3(x,y,z);}
  Vertex();
};

class Edge
{
public: 
  Vertex* v[2]; // due puntatori a Vertice (i due estremi dell'edge)
  // attributi per edge:
};

class Face
{
public: 
  Vertex* v[3]; // tre puntatori a Vertice (i tre vertici del triangolo)
  Vertex vt_tri[3]; //coordinate texture
  Vertex normal_vertex[3]; //normali per vertice di ogni faccia
  
  // costruttore
  Face(Vertex* a, Vertex* b, Vertex* c){
    v[0]=a; v[1]=b; v[2]=c;
  }
  
  // attributi per faccia
  Vector3 n; // normale (per faccia)
  
  // computa la normale della faccia
  void ComputeNormal() {
    n= -( (v[1]->p - v[0]->p) % (v[2]->p - v[0]->p) ).Normalize();
  }
  
  // attributi per wedge
};

class Mesh
{
  std::vector<Vertex> v; // vettore di vertici
  std::vector<Face> f;   // vettore di facce
  std::vector<Edge> e;   // vettore di edge (per ora, non usato)
  std::vector<Vertex> vt; //vettore vertici texture
  std::vector<Vertex> vn; //vettore normali per vertice


public:  
  
  // costruttore con caricamento

  Mesh(char *filename, float sx, float sy, float sz);
  Mesh(char *filename);
  float sx,sy,sz;
  int totFaces;
  bool gouraud;


  std::vector<Face> getFaces();
  
  // metodi
  void Render(); // manda a schermo la mesh
  
  bool LoadFromObj(char* filename); //  carica la mesh da un file OFF
  
  void ComputeNormalsPerFace();
  void ComputeNormalsPerVertex();
  void ComputeBoundingBox();
  void ScaleBoundingBox();



  //void DrawNormals();

  
  // centro del axis aligned bounding box
  Point3 Center(){ return (bbmin+bbmax)/2.0; };
  
  Point3 bbmin,bbmax; // bounding box 

};


#endif
