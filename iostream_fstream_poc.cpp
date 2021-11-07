#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <string>


int main()
{

  /*ostream initilaized with fstream*/
  std::fstream fs;
  std::ostream& ios(fs);

  fs.open("/home/ishan/cplusplus_practice/cplusplus_concepts/hello.txt", std::fstream::in | std::fstream::out | std::fstream::app);

  if(fs.is_open())
    std::cout<< "file is open"<<std::endl;
  else
    std::cout<< "file is not open"<<std::endl;

  // writing into ostream which results in writing into file hello.txt
  ios << "first line"<<std::endl;

  /* ostream initialized with stringstream object*/
  std::stringstream ss;
  // creating a pointer instead of reference 
  std::ostream* str = &ss;

  // writing into ostream, which results in wrting in string stream
  (*str) << "hello";
  std::cout<<ss.str()<<std::endl;


  /*ostream initialized with string buffer object*/
  std::stringbuf buffer;

  std::ostream stringbuftream(&buffer);

  // writing into buffer
  buffer.sputn("255 in hexdecimal:",20);
  // writing into ostream
  stringbuftream << std::hex<<255;

  // print the associated string buffer with stringbufstream
  std::cout<<stringbuftream.rdbuf();


  /*ostream initilaized with filebuf stream*/

  std::filebuf filebuffer;
  filebuffer.open("/home/ishan/cplusplus_practice/cplusplus_concepts/hello1.txt",std::ios::in|std::ios::out|std::ios::app);

  std::ostream filebufstream(&filebuffer);

  // writing into filebuffer 
  filebuffer.sputn("255 in hexdecimal:",20);

  // writing into ostream, which writes in filebuf. Thats results in writing in hello1.txt
  filebufstream<<" done";

  
}
