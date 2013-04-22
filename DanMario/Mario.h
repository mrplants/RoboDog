class Mario
{
 private:
  //The offset                                                             
  int offSet;

  // x and y coordinates                                                    
  int x;
  int y;

  //Its current frame                                                        
  int frame;

  //Its animation status                                                      
  int status;

 public:
  //Initializes the variables                                                 
  Mario();

  //Shows Mario                                                              
  void show();
};
