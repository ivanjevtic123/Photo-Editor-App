package poop;

import java.awt.Canvas;
import java.awt.Color;
import java.awt.Frame;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Scanner;

import poop.Operation.OperationType;


public class ImageCanvas extends Canvas {
	
	public enum ImageType{
		BMP, PAM, PERSONAL
	}
	private ImageType typeOfPic;
	
	private static final long serialVersionUID = 1L;
	
	private Frame frame;
	//private Pixel [][] m;
	//protected int w, h; //ako je first time, ILI NE???
	//BufferedImage bufferedImage;
	//private ArrayList<Layer> layers;// = new List<Layer>();
	private Layer mainLayer;
	
	private BasicOperation basicOp;
	private CompositeOperation compositeOp;
	
	private boolean selectionIsActive;
	private ArrayList<Selection> selections = new ArrayList<Selection>();
	Selection mainSelection;
	
	
	public ImageCanvas(Frame f) {
		this.frame = f;
		//this.layers = new ArrayList<Layer>();
		//this.mainLayer.matrix = null;
		//bufferedImage = null;
	}
	
	public void drawImage(/*Pixel [][]m*/ Layer l , int w,int h) {
		this.mainLayer = l;
		this.mainLayer.w = w;
		this.mainLayer.h = h;
		setSize(w, h);
		invalidate();
	}
	
	public boolean isInSelection(int i, int j) {
		int numOfRects=0; 
		for (Selection s : selections)
			for (Rectangle r : s.rectangles) {
				numOfRects++;
				if (r.contains(i, j)) return true;
			}
		
		if (numOfRects == 0) return true; //nema nijedan rectangle u selekciji
		
		return false;
	}
	
	@Override
	public void paint(Graphics g) {
		/*if (bufferedImage != null) {
			setSize(bufferedImage.getWidth(), bufferedImage.getHeight());
			
			g.fillRect(0, 0, getWidth(), getHeight());
			
			System.out.println( g.drawImage(bufferedImage, 0, 0, getWidth(), getHeight(), null) );*/
		
		//g.setColor(Color.WHITE);
		//g.fillRect(0, 0, getWidth(), getHeight());
		
		if(this.mainLayer != null) {
			if (this.mainLayer.matrix != null) {
				setSize(mainLayer.getW(), mainLayer.getH());
				//System.out.println(mainLayer.getW()); System.out.println(mainLayer.getH());
				for (int i=0; i<mainLayer.getH(); i++) {
					for (int j=0; j<mainLayer.getW(); j++) {
						Pixel p = mainLayer.matrix[i][j];
						//System.out.println(p.getR() + "," + p.getG() + "," + p.getB());
						g.setColor(new Color(p.getR(), p.getG(), p.getB()));
						g.drawLine(j, i, j, i);
					}
				}
			
			}
			//draw selections
			g.setColor(Color.YELLOW);
			for (Selection s:selections)
				for (Rectangle r : s.rectangles)
					g.drawRect(r.getX(), r.getY(), r.getWidth(), r.getHeight());
			
		}
	}
	
	public native byte[] readBMPData(String path);
	public native byte[] readPAMData(String path);

	public native void writeBMPData(String path, ByteBuffer bb, int num_of_bytes);
	public native void writePAMData(String path, ByteBuffer bb, int num_of_bytes);
	
	public void writeProjectToPath(String path) {
		  File myObj = new File(path);
		  PrintWriter pout = null;
		try {      
		      if (myObj.createNewFile()) {
		        System.out.println("File created: " + myObj.getName());
		      } else {
		        System.out.println("File already exists.");
		      }
		      
		      pout = new PrintWriter(myObj);
		      
		      pout.println(mainLayer.path);
		      pout.println(selections.size());
		      for (Selection s : selections) {
		    	  pout.println(s.getName());
		    	  pout.println(s.rectangles.size());
		    	  for (Rectangle r : s.rectangles)
		    		  pout.println(r);
		      }
		      
		    } catch (IOException e) {
			  System.out.println("An error occurred.");
			  e.printStackTrace();
		    } finally {
		    	if (pout != null) pout.close();
		    }
	}
	
	public void writeBMPImageToPath(String path) {
		System.loadLibrary("dz1");
		
		byte [] data = new byte[mainLayer.getW()*mainLayer.getH()*4 + 54]; //54B headeri
		
		int k = 0;
		data[k++] = 0x42;
		data[k++] = 0x4D;
		int filesize = mainLayer.getW()*mainLayer.getH()*4 + 54;
		data[k++] = (byte)filesize;
		data[k++] = (byte)(filesize >> 8);
		data[k++] = (byte)(filesize >> 16);
		data[k++] = (byte)(filesize >> 24);
		k += 4; //2B + 2B reserved
		data[k++] = 0x36;
		data[k++] = 0x00;
		data[k++] = 0x00;
		data[k++] = 0x00;
		
		data[k++] = 0x28;
		data[k++] = 0x00;
		data[k++] = 0x00;
		data[k++] = 0x00;
		int width = mainLayer.getW();
		data[k++] = (byte)width;
		data[k++] = (byte)(width >> 8);
		data[k++] = (byte)(width >> 16);
		data[k++] = (byte)(width >> 24);
		int height = mainLayer.getH();
		data[k++] = (byte)height;
		data[k++] = (byte)(height >> 8);
		data[k++] = (byte)(height >> 16);
		data[k++] = (byte)(height >> 24);
		data[k++] = 0x01;
		data[k++] = 0x00;
		data[k++] = 0x20;
		data[k++] = 0x00;
		k += 4; //compression 4B
		int imagesize = mainLayer.getW()*mainLayer.getH()*4;
		data[k++] = (byte)imagesize;
		data[k++] = (byte)(imagesize >> 8);
		data[k++] = (byte)(imagesize >> 16);
		data[k++] = (byte)(imagesize >> 24);
		k += 4; //x_pixels_per_meter TREBA DA SE IZRACUNA
		k += 4; //y_pixels_per_meter TREBA DA SE IZRACUNA
		k += 8; //colors used, colors important
		
		
		int z = k;
		for (int i = mainLayer.getH() - 1; i >= 0; i--) {
			for (int j = 0; j < mainLayer.getW(); j++) {
				int b = mainLayer.matrix[i][j].getB(); data[z] = (byte)b; z++;
				int g = mainLayer.matrix[i][j].getG(); data[z] = (byte)g; z++;
				int r = mainLayer.matrix[i][j].getR(); data[z] = (byte)r; z++;
				int a = mainLayer.matrix[i][j].getA(); data[z] = (byte)a; z++;
			}
		}
		
		
		/*for (int i = 0; i < 54; i++) {
			System.out.println(String.format("%02X ", data[i]) + " ");
		}
		System.out.println(mainLayer.getW()*mainLayer.getH()*4 + 54);*/
		ByteBuffer bb;
	    bb = ByteBuffer.allocateDirect(mainLayer.getW()*mainLayer.getH()*4 + 54);
	    bb.put(data);
		writeBMPData(path, bb, mainLayer.getW()*mainLayer.getH()*4 + 54);
	}
	
	public void writePAMImageToPath(String path) {
		System.loadLibrary("dz1");
		
		String widthStr = Integer.toString(mainLayer.getW());
		String heightStr = Integer.toString(mainLayer.getH());
		
		byte [] data = new byte[
		                        mainLayer.getW()*mainLayer.getH()*4 + widthStr.length() + heightStr.length() + 63
		                        ];
		
		int k = 0;
		byte [] first = new byte[]{ 0x50, 0x37, 0x0A, 0x57, 0x49, 0x44, 0x54, 0x48, 0x20 };
		for (int i=0; i<9; i++)
			data[k++] = first[i];
		
		for (int i=0; i<widthStr.length(); i++)
			data[k++] = (byte)widthStr.charAt(i);
		
		byte [] second = new byte[] { 0x0A, 0x48, 0x45, 0x49, 0x47, 0x48, 0x54, 0x20 };
		for (int i=0; i<8; i++)
			data[k++] = second[i];
		
		for (int i=0; i<heightStr.length(); i++)
			data[k++] = (byte)heightStr.charAt(i);
		
		byte [] third = new byte[] {
				0x0A, 0x44, 0x45, 0x50, 0x54, 0x48, 0x20, 0x34, 0x0A, 0x4D,
				0x41, 0x58, 0x56, 0x41, 0x4C, 0x20, 0x32, 0x35, 0x35, 0x0A,
				0x54, 0x55, 0x50, 0x4C, 0x54, 0x59, 0x50, 0x45, 0x20, 0x52,
				0x47, 0x42, 0x5F, 0x41, 0x4C, 0x50, 0x48, 0x41, 0x0A, 0x45,
				0x4E, 0x44, 0x48, 0x44, 0x52, 0x0A };
		for (int i=0; i<46; i++)
			data[k++] = third[i];
		
		int z = k;
		for (int i = 0; i < mainLayer.getH(); i++) {
			for (int j = 0; j < mainLayer.getW(); j++) {
				int r = mainLayer.matrix[i][j].getR(); data[z] = (byte)r; z++;
				int g = mainLayer.matrix[i][j].getG(); data[z] = (byte)g; z++;
				int b = mainLayer.matrix[i][j].getB(); data[z] = (byte)b; z++;
				int a = mainLayer.matrix[i][j].getA(); data[z] = (byte)a; z++;
			}
		}
		
		ByteBuffer bb;
	    bb = ByteBuffer.allocateDirect(mainLayer.getW()*mainLayer.getH()*4 + widthStr.length() + heightStr.length() + 63);
	    bb.put(data);
		writePAMData(path, bb, mainLayer.getW()*mainLayer.getH()*4 + widthStr.length() + heightStr.length() + 63);
	}
	
	private void readMyFormat(String path) {
		Scanner fileReader = null;
		try {
			for (Selection s:selections)
				s.rectangles.clear();
			selections.clear();
			
			fileReader = new Scanner(new File(path));
			String imagePath = fileReader.nextLine();
			System.out.println("Reading file " + imagePath);
			int numOfSelection = Integer.parseInt(fileReader.nextLine());
			System.out.println("Number of selections: " + numOfSelection);
			for (int i=0; i<numOfSelection; i++) {
				String selName = fileReader.nextLine();
				int numOfRectangles = Integer.parseInt(fileReader.nextLine());
				System.out.println("Number of rectangles: " + numOfSelection);
				
				Selection sel = new Selection(selName);
				
				for (int j=0; j<numOfRectangles; j++) {
					int x = fileReader.nextInt();
					int y = fileReader.nextInt();
					int h = fileReader.nextInt();
					int w = fileReader.nextInt();
					boolean stat = fileReader.nextBoolean();
					
					Rectangle r = new Rectangle(x, y, w, h);
					if (stat) r.setActiveStatus();
					sel.addRectangle(r);
				}
				
				selections.add(sel);
			}
			
			drawImageFromPath(imagePath);
		} catch (Exception e) {}
		finally { if (fileReader != null) fileReader.close(); }
	}
	
	public void drawImageFromPath(String path) { //Formatter treba da mi radi
		this.mainLayer = null;
		
		if (path.endsWith("txt")) { readMyFormat(path); return; }
		
		System.loadLibrary("dz1");
		//treba da pitam da li se fajl zavrsava sa pam ili bmp i da u zavisnosti od toga pozovem razlicite C++ fje
		byte [] data = null;
		if (path.endsWith("bmp")) {
			data = readBMPData(path);
		} else {
			data = readPAMData(path);
		}
		if (data.length <= 0) return;
		//System.out.println(data.length);
		
		int k = 0;
		int width = 0;
		width |= Byte.toUnsignedInt(data[k++]);
		width |= Byte.toUnsignedInt(data[k++]) << 8;
		width |= Byte.toUnsignedInt(data[k++]) << 16;
		width |= Byte.toUnsignedInt(data[k++]) << 24;
		int height = 0;
		height |= Byte.toUnsignedInt(data[k++]);
		height |= Byte.toUnsignedInt(data[k++]) << 8;
		height |= Byte.toUnsignedInt(data[k++]) << 16;
		height |= Byte.toUnsignedInt(data[k++]) << 24;
		
		int z = k;
		//System.out.println(width); System.out.println(height);
		Layer curr = new Layer(width, height, path);
		//layers.add(curr);
		//this.updateMainLayer();
		this.mainLayer = curr;
		this.mainLayer.setW(width);
		this.mainLayer.setH(height);
		mainLayer.matrix = new Pixel [height][width];
		
		//bufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB);
		
		//Od data[] pravim MatrixOfPixels
		if (path.endsWith("bmp")) {
			for (int i = height - 1; i >= 0; i--) {
				for (int j = 0; j < width; j++) {
					int b = Byte.toUnsignedInt(data[z]); z++;
					int g = Byte.toUnsignedInt(data[z]); z++;
					int r = Byte.toUnsignedInt(data[z]); z++;
					int a = Byte.toUnsignedInt(data[z]); z++;
					mainLayer.matrix[i][j] = new Pixel(r, g, b, a);
					
					//int col = (a << 24) | (r << 16) | (g << 8) | b;
					//bufferedImage.setRGB(j, i, col);
					//if (i % 100 == 0) System.out.println(bufferedImage.getRGB(j, i));
				}
			}
		} else if (path.endsWith("pam")) { //pam
			for (int i = 0; i < height; i++) {
				for (int j = 0; j < width; j++) {
					int r = Byte.toUnsignedInt(data[z]); z++;
					int g = Byte.toUnsignedInt(data[z]); z++;
					int b = Byte.toUnsignedInt(data[z]); z++;
					int a = Byte.toUnsignedInt(data[z]); z++;
					mainLayer.matrix[i][j] = new Pixel(r, g, b, a);
				}
			}
		}
		
		repaint();
		//Graphics gi = bufferedImage.createGraphics();
		//paint(gi);
		//gi.dispose();
	}
	
	/*public void assignNewMainLayer(Layer l) { //zamena layera
		this.w = l.w;
		this.h = l.h;
		for(int i = 0; i < h; i++) {
			for(int j = 0; j < w; j++) {//r, int g, int b, int a
				m[i][j]= new Pixel(l.matrix[i][j].getR(), l.matrix[i][j].getG(), 
						l.matrix[i][j].getB(), l.matrix[i][j].getA());
			}
		}
	}*/
	/*public void updateMainLayer() {
		if(layers.size() == 1){
			this.mainLayer = new Layer(this.layers.get(0));//deep, prosiri ktr ako zatreba
			this.mainLayer.matrix = new Pixel [mainLayer.getH()][mainLayer.getW()];
		}
		//dodatak pravljenje slike od vise Layera	
	}*/
	
	public void setImageType(ImageType t) {
		this.typeOfPic = t;
	}
	public ImageType getImageType() {
		return this.typeOfPic;
	}
	
	//Paket za BasicOperation:
	public void addBasicOperation(OperationType opType, int num, boolean selExists, boolean opArr, boolean last) {
		basicOp = new BasicOperation(opType, num, selectionIsActive, false, true);//PROVERI ZADNJI ARG
	}
	public void executeBasicOperation() {
		if (basicOp != null) {
			for (int i = 0; i < mainLayer.getH(); i++) {
				for (int j = 0; j < mainLayer.getW(); j++) {
					if (isInSelection(j, i)) {
						mainLayer.matrix[i][j].setActive(true);
						basicOp.setSelectionExists(true);
						basicOp.execution(mainLayer.matrix[i][j]);
					}
						
				}
			}
		}
		else {
			System.out.println("Niste uneli BasicOperation!!!");//DIJALOG DA ISKOCI!!!
		}
		basicOp = null; //unisti ga
	}

	//Paket za CompositeOperation:
	public void addCompositeOperation() {
		
	}
	public void executeCompositeOperation() {
		
	}
	public void destroyCompositeOperation() {
		
	}
	
	//Paket za Selections - dodatak
	public void setSelectionIsActive(boolean flag) {
		selectionIsActive = flag;
	}
	public void setSelectionIsActive() {
		setSelectionIsActive(true);
	}
	
	//Paket za Selections:
	public void addSelection(String name) {
		Selection s = new Selection(name);
		selections.add(s);
		if (selections.size() == 1) mainSelection = selections.get(0);
	}
	public void addSelection(Selection s) {
		selections.add(s);
		if (selections.size() == 1) mainSelection = selections.get(0);
	}
	public void choseMainSelection(String id) {
		for (int i = 0; i < selections.size(); i++) { 
			if (id == selections.get(i).getName()) {
				mainSelection = selections.get(i);
				mainSelection.updateWithAllRectangles(mainLayer, basicOp, compositeOp);
				break;
			}
		}
	}
	public void addRectangleInSelection(int x, int y, int w, int h) {//na main Selection se odnosi//uvek izaberi za main pa onda operisi sa njim
		mainSelection.createAndAddRectangle(x, y, w, h, mainLayer, basicOp, compositeOp);
		selectionIsActive = true;
	}
	public void fillMainSelectionWithColour(int r, int g, int b) {//na mainLayer se odnosi
		mainSelection.fillWithColour(mainLayer, r, g, b);
	}
	public void deleteRectangle(int index) {//brise rectangle, i updateuje celu selekciju
		mainSelection.deleteRectangle(index);
		mainSelection.updateWithAllRectangles(mainLayer, basicOp, compositeOp);
	}
	public void deleteSelection() {
		mainSelection.destroySelection(mainLayer , basicOp, compositeOp);
		//proci kroz celu sliku i setovati sve da su neaktivni mozda???
		//ne moram, jer pri choseovanju mainSelectiona updateujem celu matricu
		//ali, da li prodjem zapravo kroz celu??? provericu...
		selectionIsActive = false;
	}
	public String getSelectionName() {
		return mainSelection.getName();
	}
	
	
}
