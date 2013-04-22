//default constructor                                        
Background::Background()
{
  //Initialize the variables                                                  
  x = 0;
  y = 0;
}

void Background::show()
{
  //Show the background                                                       
  apply_surface( bgX, bgY, background, screen );
}
