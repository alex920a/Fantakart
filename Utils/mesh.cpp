// file mesh.cpp
//
// Implementazione dei metodi di Mesh

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <GL/gl.h>


#include "mesh.h"

Vertex::Vertex(){}

Mesh::Mesh(char* filename,float sx, float sy, float sz)
{
	 LoadFromObj(filename);
	ComputeNormalsPerFace();
	ComputeNormalsPerVertex(); //per il gouraud

	this->sx = sx;
	this->sy = sy;
	this->sz = sz;
	ComputeBoundingBox();

}

Mesh::Mesh(char* filename)
{
	 LoadFromObj(filename);
	ComputeNormalsPerFace();
	ComputeNormalsPerVertex(); //per il gouraud
	ComputeBoundingBox();
	this->sx = this->sy = this->sz =1;
}

void Mesh::ComputeNormalsPerFace()
{
  for (unsigned int i=0; i<f.size(); i++)
  {
    f[i].ComputeNormal();

  }
}

// Computo normali per vertice
// (come media rinormalizzata delle normali delle facce adjacenti)
void Mesh::ComputeNormalsPerVertex()
{
  // uso solo le strutture di navigazione FV (da Faccia a Vertice)!

  // fase uno: ciclo sui vertici, azzero tutte le normali
  for (int i=0; i<v.size(); i++) {
    v[i].n = Point3(0,0,0);
  }

  // fase due: ciclo sulle facce: accumulo le normali di F nei 3 V corrispondenti
  for (int i=0; i<f.size(); i++) {
    f[i].v[0]->n=f[i].v[0]->n + f[i].n;
    f[i].v[1]->n=f[i].v[1]->n + f[i].n;
    f[i].v[2]->n=f[i].v[2]->n + f[i].n;
  }

  // fase tre: ciclo sui vertici; rinormalizzo
  // la normale media rinormalizzata e' uguale alla somma delle normnali, rinormalizzata
  for (int i=0; i<v.size(); i++) {
    v[i].n = v[i].n.Normalize();
  }

}

//void Mesh::DrawNormals()
//{
//	int i;
//	for(i=0;i<f.size();i++)
//	{
//		Face temp = f.at(i);
//
//
//
//
//		//calcolo il centro della faccia:
//		float x_c = (temp.v[0]->p.X() +temp.v[1]->p.X() + temp.v[2]->p.X())/3.0f;
//		float y_c = (temp.v[0]->p.Y() +temp.v[1]->p.Y() + temp.v[2]->p.Y())/3.0f;
//		float z_c = (temp.v[0]->p.Z() +temp.v[1]->p.Z() + temp.v[2]->p.Z())/3.0f;
//
//		//std::cout<<" x,y, z center:"<< x_c<<" "<<y_c<<" "<<z_c<<std::endl;
//
//		Point3 center( x_c, y_c, z_c);
//
//		Point3 a = center + temp.n;
//		Point3 b = center - temp.n;
//
//
//		glDisable(GL_LIGHTING);
//		glColor3f(1,0,0);
//		glBegin(GL_LINES);
//		glVertex3f(a.X(), a.Y(), a.Z());
//		glVertex3f(b.X(), b.Y(), b.Z());
//		glEnd();
//
////		glBegin(GL_POINTS);
////		glVertex3f(x_c, y_c, z_c);
////
////		glEnd();
//	}
//}

void Mesh::Render() //gouraud
{
  // mandiamo tutti i triangoli a schermo
  glBegin(GL_TRIANGLES);

  for (unsigned int i=0; i<f.size(); i++)
  {
	  if(!gouraud)
		  f[i].n.SendAsNormal(); // flat shading

    glTexCoord2d(f[i].vt_tri[0].p.coord[0], 1-0-f[i].vt_tri[0].p.coord[1]);
    if(gouraud) (f[i].v[0])->n.SendAsNormal();
    (f[i].v[0])->p.SendAsVertex();

    
    glTexCoord2d(f[i].vt_tri[2].p.coord[0], 1.0-f[i].vt_tri[2].p.coord[1]);
    if(gouraud)(f[i].v[1])->n.SendAsNormal();
    (f[i].v[1])->p.SendAsVertex();

    
    glTexCoord2d(f[i].vt_tri[1].p.coord[0], 1.0-f[i].vt_tri[1].p.coord[1]);
    if(gouraud)(f[i].v[2])->n.SendAsNormal();
    (f[i].v[2])->p.SendAsVertex();

  }


  glEnd();
}

void Mesh::ComputeBoundingBox(){
  if (!v.size()) return;
  bbmin=bbmax=v[0].p;
  for (int i=0; i<v.size(); i++){
    for (int k=0; k<3; k++) {
      if (bbmin.coord[k]>v[i].p.coord[k]) bbmin.coord[k]=v[i].p.coord[k];
      if (bbmax.coord[k]<v[i].p.coord[k]) bbmax.coord[k]=v[i].p.coord[k];
    }
  }




}


void Mesh::ScaleBoundingBox()
{

	//std::cout<<" sx,sy,sz:"<<sx<<" "<<sy<<" "<<sz<<std::endl;



	bbmax.coord[0] /= this->sx;  bbmin.coord[0] /= this->sx;
	bbmax.coord[1] /= this->sy;  bbmin.coord[1] /= this->sy;
	bbmax.coord[2] /= this->sz;  bbmin.coord[2] /= this->sz;
}





bool Mesh::LoadFromObj(char* filename)
{
  
  FILE* file = fopen(filename, "rt"); // apriamo il file in lettura

  if (!file) return false;


  //make a first pass through the file to get a count of the number
  //of vertices, normals, texcoords & triangles 
  char buf[128];
  int nv,nf,nt;
  float x,y,z,u,t;
  int va,vb,vc,vd;
  int na,nb,nc,nd;
  int ta,tb,tc,td;
  int numtexcoords=0, numNormals = 0;


  nv=0; nf=0; nt=0;
  while(fscanf(file, "%s", buf) != EOF) {
        switch(buf[0]) {
        case '#':               // comment
            // eat up rest of line
            fgets(buf, sizeof(buf), file);
            break;

        case 'v':               // v, vn, vt
            switch(buf[1]) {
            case '\0':          // vertex
                // eat up rest of line 
                fgets(buf, sizeof(buf), file);
                nv++;
                break;
            case 't':           /* texcoord */
				 /* eat up rest of line */
				fgets(buf, sizeof(buf), file);
				numtexcoords++;

				//std::cout<<"tot tex coord:"<<numtexcoords<<std::endl;
				 break;

            case 'n':           /* texcoord */
				 /* eat up rest of line */
				fgets(buf, sizeof(buf), file);
				numNormals++;

				//std::cout<<"tot tex coord:"<<numNormals<<std::endl;
				 break;
            default:
                break;
            }
            break;
         case 'f':               // face
                fscanf(file, "%s", buf);
                // can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d
                if (strstr(buf, "//")) {
                    // v//n
                    sscanf(buf, "%d//%d", &va, &na);
                    fscanf(file, "%d//%d", &vb, &nb);
                    fscanf(file, "%d//%d", &vc, &nc);
                    nf++;
                    nt++;
                    while(fscanf(file, "%d//%d", &vd, &nd) > 0) {
                        nt++;
                    }
                } else if (sscanf(buf, "%d/%d/%d", &va, &ta, &na) == 3) {
                    // v/t/n
                    fscanf(file, "%d/%d/%d", &vb, &tb, &nb);
                    fscanf(file, "%d/%d/%d", &vc, &tc, &nc);
                    nf++;
                    nt++;
                    while(fscanf(file, "%d/%d/%d", &vd, &td, &nd) > 0) {
                        nt++;
                    }
                 } else if (sscanf(buf, "%d/%d", &va, &ta) == 2) {
                    // v/t
                    fscanf(file, "%d/%d", &vb, &tb);
                    fscanf(file, "%d/%d", &vc, &tc);
                    nf++;
                    nt++;
                    while(fscanf(file, "%d/%d", &vd, &td) > 0) {
                        nt++;
                    }
                } else {
                    // v
                    fscanf(file, "%d", &va);
                    fscanf(file, "%d", &vb);
                    nf++;
                    nt++;
                    while(fscanf(file, "%d", &vc) > 0) {
                        nt++;
                    }
                }
                break;

            default:
                // eat up rest of line
                fgets(buf, sizeof(buf), file);
                break;
        }

       // giro++;
   }
 
//printf("dopo FirstPass nv=%d nf=%d nt=%d\n",nv,nf,nt);
  
  // allochiamo spazio per nv vertici
  v.resize(nv);
  vt.resize(numtexcoords);
  vn.resize(numNormals);

 // std::cout<<"tot tex coord:"<<numtexcoords;
  // std::cout<<"tot normals:"<<numNormals;

  // rewind to beginning of file and read in the data this pass
  rewind(file);
  
  //on the second pass through the file, read all the data into the
  //allocated arrays

  nv = 0;
  numtexcoords =numNormals= 0;
  float nx,ny,nz;


  while(fscanf(file, "%s", buf) != EOF) {
      switch(buf[0]) {
      case '#':               // comment
            // eat up rest of line
            fgets(buf, sizeof(buf), file);
            break;
      case 'v':               // v, vn, vt
            switch(buf[1]) {
            case '\0':          // vertex
                fscanf(file, "%f %f %f", &x, &y, &z);
                v[nv].p = Point3( x,y,z );
                nv++;
                break;

            case 't': //texture coord
            	fscanf(file, "%f %f ", &u, &t);
				vt[numtexcoords].p = Point3( u,t,0 );
				numtexcoords++;
				break;

            case 'n': //normali
				fscanf(file, "%f %f %f", &nx,&ny,&nz);
				vn[numNormals].p = Point3( nx,ny,nz );
				numNormals++;
				break;


            default:
                break;
            }
            break;


     case 'f':               // face
           fscanf(file, "%s", buf);
           // can be one of %d, %d//%d, %d/%d, %d/%d/%d %d//%d
           if (strstr(buf, "//")) {
              // v//n
              sscanf(buf, "%d//%d", &va, &na);
              fscanf(file, "%d//%d", &vb, &nb);
              fscanf(file, "%d//%d", &vc, &nc);
              va--; vb--; vc--;
              Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia
              f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
              nt++;
              vb=vc;
              while(fscanf(file, "%d//%d", &vc, &nc) > 0) {
                 vc--;
                 Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia
                 f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
                 nt++;
                 vb=vc;
              }
           } else if (sscanf(buf, "%d/%d/%d", &va, &ta, &na) == 3) {
                // v/t/n
                fscanf(file, "%d/%d/%d", &vb, &tb, &nb);
                fscanf(file, "%d/%d/%d", &vc, &tc, &nc);
                va--; vb--; vc--;
                Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia

                //coordinate textures
                newface.vt_tri[0] = vt.at(ta-1);
                newface.vt_tri[1] = vt.at(tb-1);
                newface.vt_tri[2] = vt.at(tc-1);
                //normali per vertice
                newface.normal_vertex[0]= vn.at(na-1);
                newface.normal_vertex[1]= vn.at(nb-1);
                newface.normal_vertex[2]= vn.at(nc-1);

                f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
                nt++;
                vb=vc;
                while(fscanf(file, "%d/%d/%d", &vc, &tc, &nc) > 0) { // per facce non triangolari
                   vc--;
                   Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia
                   f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
                   nt++;
                   vb=vc;
                }
           } else if (sscanf(buf, "%d/%d", &va, &ta) == 2) {
                // v/t
                fscanf(file, "%d/%d", &va, &ta);
                fscanf(file, "%d/%d", &va, &ta);
                va--; vb--; vc--;
                Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia
                f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
                nt++;
                vb=vc;
                while(fscanf(file, "%d/%d", &vc, &tc) > 0) {
                   vc--;
                   Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia
                   f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
                   nt++;
                   vb=vc;
                }
           } else {
                // v
                sscanf(buf, "%d", &va);
                fscanf(file, "%d", &vb);
                fscanf(file, "%d", &vc);
                va--; vb--; vc--;
                Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia
                f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
                nt++;
                vb=vc;
                while(fscanf(file, "%d", &vc) > 0) {
                   vc--;
                   Face newface( &(v[va]), &(v[vc]), &(v[vb]) ); // invoco il costruttore di faccia
                   f.push_back( newface ); // inserico la nuova faccia in coda al vettore facce
                   nt++;
                   vb=vc;
                }
            }
            break;

            default:
                // eat up rest of line
                fgets(buf, sizeof(buf), file);
                break;
    }
  }

//printf("dopo SecondPass nv=%d nt=%d\n",nv,nt);
  totFaces = nf;
 // std::cout<<"tot faces:"<< totFaces<<std::endl;

  fclose(file);
  return true;
}


std::vector<Face> Mesh::getFaces()
{
	return f;
}



