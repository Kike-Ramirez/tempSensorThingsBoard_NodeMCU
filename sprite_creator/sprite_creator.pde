/**
 * Loop. 
 * 
 * Shows how to load and play a QuickTime movie file.  
 *
 */

import processing.video.*;
import interfascia.*;

GUIController c;
IFTextField original_width, original_height;
IFLabel original_width_label, original_height_label;

IFTextField sprite_width, sprite_height, num_frames;
IFLabel sprite_width_label, sprite_height_label, num_frames_label;

IFButton generate_button, exit_button, load_button, save_button;
IFProgressBar generate_bar;
IFRadioController adjust_controller;
IFRadioButton h_button, v_button;



Movie movie;
PImage frame, sprite;
int deltaX, deltaY;
boolean converting;
int index_frame;
String video_url;

void load_video(File selection) {
  
  if (selection == null) {
    video_url = "";
  } else {
    video_url = selection.getPath();
    println(video_url);
  }
  
  video_url = video_url.toLowerCase();
  
  while ((!video_url.endsWith("mp4") && !video_url.endsWith("gif") && !video_url.endsWith("mov") && !video_url.endsWith("mpg")) || video_url.length() <= 0) {
    
    println("Please, select a video"); 
    delay(1000);
  
  }
  
  movie = new Movie(this, video_url);
  movie.play();
  
  while (!movie.available()) {
  }
  
  movie.read();
  movie.pause();
  
  index_frame = 0;
  
  converting = false;
  movie.stop();  
  
}

void fileSelected(File selection) {
  if (selection == null) {
    video_url = "";
  } else {
    video_url = selection.getAbsolutePath();
    println(video_url);
  }
}

void setup() {
  
  size(1024, 768);
  
  background(150);
  
  // Calculate deltas for GUI Positioning
  deltaX = int(width * 0.05);
  deltaY = int(height * 0.04);
  
  video_url = "bees&bombs_000.mp4";
  
  movie = null;
  File selected = new File(video_url);
  load_video(selected);
  
  
  while (movie == null) delay(500);
  
  // Set GUI
  c = new GUIController(this);

  // Original Resolution & Frame Number
  original_width = new IFTextField("original_width", deltaX, int(2 * deltaY), 2 * deltaX);
  original_height = new IFTextField("original_height", deltaX, int(4 * deltaY), 2 * deltaX);
  num_frames = new IFTextField("Frame Number", deltaX, int(6 * deltaY), 2 * deltaX);
  
  original_width_label = new IFLabel("Original Width", deltaX, int(1.5 * deltaY));
  original_height_label = new IFLabel("Original Height", deltaX, int(3.5 * deltaY));
  num_frames_label = new IFLabel("Frame Number", deltaX, int(5.5 * deltaY));

  original_width.setValue(str(movie.width));
  original_height.setValue(str(movie.height));
  num_frames.setValue(str(int(movie.duration() * movie.frameRate)));
  
  // Desired sprite output resolution & Generate Button & Progress Bar
  sprite_width_label = new IFLabel("Output Width", deltaX, int(11.5 * deltaY));
  sprite_width = new IFTextField("sprite_width", deltaX, int(12 * deltaY), int(2 * deltaX));
  
  sprite_height_label = new IFLabel("Output Height", deltaX, int(13.5 * deltaY));
  sprite_height = new IFTextField("sprite_height", deltaX, int(14 * deltaY), int(2 * deltaX));
  
  sprite_width.setValue(str(128));
  sprite_height.setValue(str(32));
  
  adjust_controller = new IFRadioController("adjust");
  h_button = new IFRadioButton("h", deltaX, int(16 * deltaY), adjust_controller);
  v_button = new IFRadioButton("v", 2 * deltaX, int(16 * deltaY), adjust_controller);
  
  load_button = new IFButton("Load Video", int(17 * deltaX), int(18 * deltaY));
  load_button.setHeight(int(2 * deltaY));
  load_button.addActionListener(this);
  
  save_button = new IFButton("Save Sprite", int(17 * deltaX), int(20 * deltaY));
  save_button.setHeight(int(2 * deltaY));
  save_button.addActionListener(this);
  
  generate_button = new IFButton("CONVERT", int(deltaX), int(22 * deltaY));
  generate_button.setHeight(int(2 * deltaY));
  generate_button.addActionListener(this);
  
  generate_bar = new IFProgressBar(int(3.5 * deltaX), int(22 * deltaY), 13 * deltaX);
  generate_bar.setHeight(int(2 * deltaY));
  generate_bar.setProgress(0);

  exit_button = new IFButton("EXIT", int(17 * deltaX), int(22 * deltaY));
  exit_button.setHeight(int(2 * deltaY));
  exit_button.addActionListener(this);
  

  
  // Add components to GUI
  c.add(original_width);
  c.add(original_width_label);
  c.add(original_height);
  c.add(original_height_label);
  c.add(num_frames);
  c.add(num_frames_label);
  c.add(sprite_width);
  c.add(sprite_width_label);
  c.add(sprite_height);
  c.add(sprite_height_label);
  c.add(adjust_controller);
  c.add(h_button);
  c.add(v_button);
  c.add(load_button);
  c.add(save_button);
  c.add(generate_button);
  c.add(generate_bar);
  c.add(exit_button);
  
  sprite = createImage(int(sprite_width.getValue()), int(num_frames.getValue()) * int(sprite_height.getValue()), RGB);
  
}


void movieEvent(Movie m) {
  m.read();
}

void createSprite() {
  sprite = createImage(int(sprite_width.getValue()), int(num_frames.getValue()) * int(sprite_height.getValue()), RGB);
  sprite.loadPixels();
  for (int i = 0; i < sprite.pixels.length; i++) {
    sprite.pixels[i] = color(0);
  }
  sprite.updatePixels();
}

void generateSprite() {
  
}

void draw() {

  background(150);

  image(movie, 4 * deltaX, deltaY);
  
  
  stroke(255, 0, 0);
  noFill();
  
  PImage captured_frame;
  int rect_width, rect_height;
  
  if (adjust_controller.getSelectedIndex() == 1) {
    rect_height = movie.height;
    rect_width = int(float(movie.width) * rect_height / float(sprite_height.getValue()));
    rect(4 * deltaX, deltaY, rect_width, rect_height);  
  }

  else {
    rect_width = movie.width;
    rect_height = int(float(movie.height) * float(sprite_width.getValue()) / rect_width );
    rect(4 * deltaX, deltaY + (movie.height - rect_height) * 0.5, rect_width, rect_height);  
  }
  
  if (converting) {
    
    if (movie.time() >= movie.duration()) {
      movie.stop();
      generate_bar.setProgress(0);
      converting = false;
    }
    
    else 
    {
      generate_bar.setProgress(movie.time() / movie.duration());
      if (adjust_controller.getSelectedIndex() == 1) captured_frame = movie.get(0, 0, rect_width, rect_height);
      else captured_frame = movie.get(0, int((movie.height - rect_height) * 0.5), rect_width, rect_height);
      captured_frame.filter(THRESHOLD, 0.3);
      captured_frame.resize(int(sprite_width.getValue()), int(sprite_height.getValue()));
      sprite.set(0, index_frame * int(sprite_height.getValue()), captured_frame);
      index_frame++;

    }
  }
  
  int sprite_height = 20 * deltaY;
  int sprite_width = int(sprite.width * sprite_height / float(sprite.height));
  image(sprite, 5 * deltaX + movie.width, deltaY, sprite_width, sprite_height);

}

void actionPerformed (GUIEvent e) {
  if (e.getSource() == generate_button) {
    if (!converting) {
      converting = true;
      movie.play();
      index_frame = 0;
    }
  }
  else if (e.getSource() == sprite_width) {
    createSprite();
  }
  else if (e.getSource() == sprite_height) {
    createSprite();
  }
  else if (e.getSource() == exit_button) {
    exit();
  }  
  else if (e.getSource() == load_button) {
    selectInput("Select a VIDEO file to process:", "load_video");
  }  
  else if (e.getSource() == save_button) {
    sprite.save("sprite_output.bmp");

  }  
}
