#include <Rcpp.h>
#include "rxitari.h"


using namespace Rcpp ; 

class AtariGame{
private:
  std::unique_ptr<XitariALE> _ale;
  double age;
  double GPA;
public:
  AtariGame(const char *rom_file){}
  
  double sum(double x, double myGPA){
    GPA = myGPA;
    return GPA + x;
  }
  double times(double x, double myage){
    age = myage;
    return age*GPA*x;
  }
};


RCPP_MODULE(my_module){
  
  
  class_<AtariGame>("AtariGame")
    .constructor<const char *>()
    .method("sum", &AtariGame::sum, "Sum")      // Add some documentation (optional)
    .method("times",&AtariGame::times, "Times");
}