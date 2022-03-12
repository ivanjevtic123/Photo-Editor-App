package poop;

import java.awt.BorderLayout;
import java.awt.Button;
import java.awt.Color;
import java.awt.Frame;
import java.awt.GridLayout;
import java.awt.Menu;
import java.awt.MenuBar;
import java.awt.Panel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.io.File;
import java.io.IOException;
import java.io.PrintWriter;

import javax.swing.filechooser.FileFilter;

import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

import javax.swing.JFileChooser;
import javax.swing.JOptionPane;

import poop.Operation.OperationType;

public class Main extends Frame {
	final public static int FRAME_WIDTH = 1366;
	final public static int FRAME_HEIGHT = 900;

	private Pixel [][]mat;
	private int width, height;
	private ImageCanvas imageCanvas;
	private Panel toolbar;
	final private Main parentFrame = this;
	private ArrayList<Integer> compositeOperation = new ArrayList<>();
	private boolean selectionMode = false;
	
	private MouseAdapter canvasMouseListener = new MouseAdapter() {
		private int numberOfClicks = 0;
		private int x1, y1;
		@Override
		public void mouseClicked(MouseEvent event) {
			if (selectionMode == false) return;
			
			numberOfClicks++;
			if (numberOfClicks == 1) {
				x1 = event.getX();
				y1 = event.getY();
				
				parentFrame.setTitle("First point (" + x1 + "," + y1 + "), click for second rectangle point...");
			} else { //==2
				numberOfClicks = 0;
				selectionMode = false;
				
				int x2 = event.getX();
				int y2 = event.getY();
				
				parentFrame.imageCanvas.addRectangleInSelection(x1, y1, x2-x1, y2-y1);
				System.out.println("Added new rectangle (" + x1 + "," + y1 +")(" + x2 + "," + y2 + ")");
				Rectangle r = parentFrame.imageCanvas.mainSelection.rectangles.get(0);
				if (r != null)
					System.out.println("Added new rectangle (" + r.getX() + "," + r.getY() +")(w:" + r.getWidth() + ",h:" + r.getHeight() + ")");
				parentFrame.setTitle("POOP");
				
				parentFrame.imageCanvas.repaint();
			}
			
		}
		
	};
	
	
	private ActionListener menuListener = new ActionListener() {
		@Override
		public void actionPerformed(ActionEvent e) {
			if (e.getActionCommand().equals("Open")) {
				JFileChooser fc = new JFileChooser();
				fc.setAcceptAllFileFilterUsed(false);
				fc.addChoosableFileFilter(new FileFilter() {
				    public String getDescription() {
				        return "BMP Documents (*.bmp)";
				    }
				 
				    public boolean accept(File f) {
				        if (f.isDirectory()) {
				            return true;
				        } else {
				            return f.getName().toLowerCase().endsWith(".bmp");
				        }
				    }
				});
				fc.addChoosableFileFilter(new FileFilter() {
				    public String getDescription() {
				        return "PAM Documents (*.pam)";
				    }
				 
				    public boolean accept(File f) {
				        if (f.isDirectory()) {
				            return true;
				        } else {
				            return f.getName().toLowerCase().endsWith(".pam");
				        }
				    }
				});
				fc.addChoosableFileFilter(new FileFilter() {
				    public String getDescription() {
				        return "My format (*.txt)";
				    }
				 
				    public boolean accept(File f) {
				        if (f.isDirectory()) {
				            return true;
				        } else {
				            return f.getName().toLowerCase().endsWith(".txt");
				        }
				    }
				});
				
				fc.addChoosableFileFilter(new FileFilter() {
				    public String getDescription() {
				        return "Composite operation (*.fun)";
				    }
				 
				    public boolean accept(File f) {
				        if (f.isDirectory()) {
				            return true;
				        } else {
				            return f.getName().toLowerCase().endsWith(".fun");
				        }
				    }
				});
				
				int returnVal = fc.showOpenDialog(Main.this);
				fc.setDialogTitle("Specify a file to open"); 

		        if (returnVal == JFileChooser.APPROVE_OPTION) {
		            File file = fc.getSelectedFile();
		            
		            if (file.getAbsolutePath().endsWith("fun")) {
		            	loadAndExecuteCompositeOperation(file.getAbsolutePath());
		            	return;
		            }
		            
		            System.out.println("Opening: " + file.getAbsoluteFile() + "\n");
		            if (imageCanvas != null) {
		            	imageCanvas.drawImageFromPath(file.getAbsolutePath());
		            }
		        } else {
		        	System.out.println("Open command cancelled by user\n");
		        }
			}
			if (e.getActionCommand().equals("BMP")) { //za SAVE AS
				JFileChooser fc = new JFileChooser();
				fc.setDialogTitle("Specify a file to save"); 
				fc.setAcceptAllFileFilterUsed(false);
				fc.addChoosableFileFilter(new FileFilter() {
				    public String getDescription() {
				        return "BMP Documents (*.bmp)";
				    }
				 
				    public boolean accept(File f) {
				        if (f.isDirectory()) {
				            return true;
				        } else {
				            return f.getName().toLowerCase().endsWith(".bmp");
				        }
				    }
				});
				
				int returnVal = fc.showSaveDialog(Main.this);
				

		        if (returnVal == JFileChooser.APPROVE_OPTION) {
		            File file = fc.getSelectedFile();
		            
		            if (imageCanvas != null) {
		            	imageCanvas.writeBMPImageToPath(file.getAbsolutePath());
		            }
		            System.out.println("Saving: " + file.getAbsoluteFile() + "\n");
		        } else {
		        	System.out.println("Save command cancelled by user\n");
		        }
			}
			if (e.getActionCommand().equals("PAM")) { //za SAVE AS
				JFileChooser fc = new JFileChooser();
				fc.setDialogTitle("Specify a file to save"); 
				fc.setAcceptAllFileFilterUsed(false);
				fc.addChoosableFileFilter(new FileFilter() {
				    public String getDescription() {
				        return "PAM Documents (*.pam)";
				    }
				 
				    public boolean accept(File f) {
				        if (f.isDirectory()) {
				            return true;
				        } else {
				            return f.getName().toLowerCase().endsWith(".pam");
				        }
				    }
				});
				
				int returnVal = fc.showSaveDialog(Main.this);
				

		        if (returnVal == JFileChooser.APPROVE_OPTION) {
		            File file = fc.getSelectedFile();
		            
		            if (imageCanvas != null) {
		            	imageCanvas.writePAMImageToPath(file.getAbsolutePath());
		            }
		            System.out.println("Saving: " + file.getAbsoluteFile() + "\n");
		        } else {
		        	System.out.println("Save command cancelled by user\n");
		        }
			}
			if (e.getActionCommand().equals("PersonalFormat")) {//za SAVE AS
				JFileChooser fc = new JFileChooser();
				fc.setDialogTitle("Specify a file to save"); 
				fc.setAcceptAllFileFilterUsed(false);
				fc.addChoosableFileFilter(new FileFilter() {
				    public String getDescription() {
				        return "Personal format (*.txt)";
				    }
				 
				    public boolean accept(File f) {
				        if (f.isDirectory()) {
				            return true;
				        } else {
				            return f.getName().toLowerCase().endsWith(".txt");
				        }
				    }
				});
				
				int returnVal = fc.showSaveDialog(Main.this);
				

		        if (returnVal == JFileChooser.APPROVE_OPTION) {
		            File file = fc.getSelectedFile();
		            
		            if (imageCanvas != null) {
		            	imageCanvas.writeProjectToPath(file.getAbsolutePath());
		            }
		            System.out.println("Saving: " + file.getAbsoluteFile() + "\n");
		        } else {
		        	System.out.println("Save command cancelled by user\n");
		        }
			}
			if (e.getActionCommand().equals("Exit")) {
				dispose();
			}
			
			//Selection:
			if(e.getActionCommand().equals("AddNewRectangle")) {
				parentFrame.setTitle("Selection mode, click to get starting rectangle point...");
				selectionMode = true;
				/*String nameOfSelection = showInputDialog("Uneti naziv selekcije:");
		        if(nameOfSelection != null && nameOfSelection.length() > 0) {
		        	try {
			            imageCanvas.addSelection(nameOfSelection);
			            //System.out.println(imageCanvas.getSelectionName());
						//imageCanvas.repaint();//HMM????
		        	} catch (NumberFormatException ex) {}
		        }*/
			}
			if(e.getActionCommand().equals("SelectMainSelection")) { 
				/*String nameOfMainSelection = showInputDialog("Uneti naziv glavne selekcije:");
		        if(nameOfMainSelection != null && nameOfMainSelection.length() > 0) {
		        	try {
			            imageCanvas.addSelection(nameOfMainSelection);
			            imageCanvas.choseMainSelection(nameOfMainSelection);
						//imageCanvas.repaint();//HMM????
		        	} catch (NumberFormatException ex) {} //Dobar izuzetak???
		        }*/
			}
			if(e.getActionCommand().equals("DeleteMainSelection")) { 
				//imageCanvas.deleteSelection();
			}
			if(e.getActionCommand().equals("FillWithColour")) { 
				/*
				cout << "Uneti komponentu RED:" << endl;
			int r;
			cin >> r;
			cout << endl;

			cout << "Uneti komponentu GREEN:" << endl;
			int g;
			cin >> g;
			cout << endl;

			cout << "Uneti komponentu BLUE:" << endl;
			int b;
			cin >> b;
			cout << endl;

			project.fillMainSelectionWithColour(r, g, b);
				 */
				int rr = 0, gg = 0, bb = 0;
				String red = showInputDialog("Input RED:");
				if(red != null && red.length() > 0) {
					try {
						rr = Integer.parseInt(red);
						//imageCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}
				
				String green = showInputDialog("Input GREEN:");
				if(green != null && green.length() > 0) {
					try {
						gg = Integer.parseInt(green);
						//imageCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}
				
				String blue = showInputDialog("Input BLUE:");
				if(blue != null && blue.length() > 0) {
					try {
						bb = Integer.parseInt(blue);
						//imageCanvas.repaint();
					} catch (NumberFormatException ex) {}
				}
				
				imageCanvas.fillMainSelectionWithColour(rr, gg, bb);
				
				imageCanvas.repaint(); 
			}
			
			//BasicOperations:
			if(e.getActionCommand().equals("ADD")) { 
				executeOperationD(OperationType.ADD);
			}
			if(e.getActionCommand().equals("SUB")) { 
				executeOperationD(OperationType.SUB);
			}
			if(e.getActionCommand().equals("INVSUB")) { 
				executeOperationD(OperationType.INVSUB);
			}
			if(e.getActionCommand().equals("MUL")) { 
				executeOperationD(OperationType.MUL);
			}
			if(e.getActionCommand().equals("DIV")) { 
				executeOperationD(OperationType.DIV);
			}
			if(e.getActionCommand().equals("INVDIV")) { 
				executeOperationD(OperationType.INVDIV);
			}
			if(e.getActionCommand().equals("POW")) { 
				executeOperationD(OperationType.POW);
			}
			if(e.getActionCommand().equals("LOG")) { 
				executeOperationD(OperationType.LOG);
			}
			if(e.getActionCommand().equals("ABS")) { 
				executeOperationD(OperationType.ABS);
			}
			if(e.getActionCommand().equals("MIN")) { 
				executeOperationD(OperationType.MIN);
			}
			if(e.getActionCommand().equals("MAXIM")) { 
				executeOperationD(OperationType.MAXIM);
			}
			if(e.getActionCommand().equals("INV")) { 
				executeOperationD(OperationType.INV);
			}
			if(e.getActionCommand().equals("GRAY")) { 
				executeOperationD(OperationType.GRAY);
			}
			if(e.getActionCommand().equals("BNW")) { 
				executeOperationD(OperationType.BNW);
			}
			if(e.getActionCommand().equals("MED")) { 
				executeOperationD(OperationType.MED);
			}
			/*if(e.getActionCommand().equals("COMP")) { 
				executeOperationD(OperationType.COMP);//NEEEEEEEE
			}*/

			if(e.getActionCommand().equals("CompositeOperations")) { 
				String[] values = { "ADD", "SUB", "INVSUB", "MUL", "DIV", "INVDIV", "POW", "LOG", "ABS", "MIN", "MAXIM", "INV", "GRAY", "BNW", "MED", "COMP", "EXECUTE ALL", "SAVE COMPOSITE"};

				Object selected = JOptionPane.showInputDialog(null, "Choose operation?", "Composite Operation", JOptionPane.DEFAULT_OPTION, null, values, "0");
				if ( selected != null ){//null if the user cancels. 
				    String selectedString = selected.toString();
				    
				    if (selectedString.equals("EXECUTE ALL")) {
				    	//run composite operation
				    	Object [] opsInt = compositeOperation.toArray();
				    	compositeOperation.clear();
				    	int [] operations = new int[opsInt.length];
				    	for (int i=0; i<operations.length; i++) {
				    		operations[i] = ((Integer)opsInt[i]).intValue();
				    		System.out.println(operations[i]);
				    	}
				    	
				    	parentFrame.executeCompositeOperations(operations);
				    	
				    	return;
				    }
				    
				    if (selectedString.equals("SAVE COMPOSITE")) {
				    	
				    	JFileChooser fc = new JFileChooser();
						fc.setDialogTitle("Specify a composite function file to save"); 
						fc.setAcceptAllFileFilterUsed(false);
						fc.addChoosableFileFilter(new FileFilter() {
						    public String getDescription() {
						        return "Composite operation (*.fun)";
						    }
						 
						    public boolean accept(File f) {
						        if (f.isDirectory()) {
						            return true;
						        } else {
						            return f.getName().toLowerCase().endsWith(".fun");
						        }
						    }
						});
						
						int returnVal = fc.showSaveDialog(Main.this);
						

				        if (returnVal == JFileChooser.APPROVE_OPTION) {
				            File file = fc.getSelectedFile();
				            PrintWriter pout = null;
				            
				            try {      
				  		      if (file.createNewFile()) {
				  		        System.out.println("File created: " + file.getName());
				  		      } else {
				  		        System.out.println("File already exists.");
				  		      }
				  		      
				  		      pout = new PrintWriter(file);
				  		      
				  		      	//save composite operation
						    	Object [] opsInt = compositeOperation.toArray();
						    	compositeOperation.clear();
						    	int [] operations = new int[opsInt.length];
						    	for (int i=0; i<operations.length; i++) {
						    		operations[i] = ((Integer)opsInt[i]).intValue();
						    		
						    		pout.println(operations[i]);
						    	}
				  		      
				  		    } catch (IOException ex) {
				  			  System.out.println("An error occurred.");
				  			  ex.printStackTrace();
				  		    } finally {
				  		    	if (pout != null) pout.close();
				  		    }
				          
				        } else {
				        	System.out.println("Save command cancelled by user\n");
				        }
				    	
				    	return;
				    }
				    int i = 0;
				    for (i=0; i<values.length; i++) 
				    	if (selectedString.equals(values[i])) break;
				    
				    compositeOperation.add(i);
				    
				    System.out.println("number of operation: " + i); //i je enum broj (id) operacije
				}else{
				    System.out.println("User cancelled");
				}
			}
			
			if(e.getActionCommand().equals("AddNewLayer")) { 
				
			}
			if(e.getActionCommand().equals("UpdateMainLayer")) { 
				
			}
			if(e.getActionCommand().equals("DeleteMainLayer")) { 
				
			}
			if(e.getActionCommand().equals("SelectMainLayer")) { 
				
			}
			if(e.getActionCommand().equals("ShowNames")) { 
				
			}
			
			if(e.getActionCommand().equals("AddNewRectangle")) { //treba misem da crtam, hmm...
				/*int x = 0, y = 0, w = 0, h = 0;
				//...MOUSE DRAGGED, citaj prvu i zadnju(x1,y1; x2,y2), izracunaj w i h iz toga
				imageCanvas.addRectangleInSelection(x, y, w, h);*/
			}
			if(e.getActionCommand().equals("DeleteRectangle")) {//kako 
				
			}
		}
	};
	
	private String showInputDialog(String title) {
		String result = (String)JOptionPane.showInputDialog(
		           this,
		           "Input value", 
		           title,            
		           JOptionPane.PLAIN_MESSAGE,
		           null,            
		           null, 
		           "0"
		        );
		
		return result;
	}
	
	private void loadAndExecuteCompositeOperation(String path) {
		Scanner fileReader = null;
		try {
			compositeOperation.clear();
			
			fileReader = new Scanner(new File(path));
			ArrayList<Integer> ops = new ArrayList<Integer>();
			while (fileReader.hasNextInt()) {
				int opcode = fileReader.nextInt();
				ops.add(new Integer(opcode));
			}
				
			int [] operations = new int[ops.size()];
			for (int i=0; i<ops.size(); i++)
				operations[i] = ops.get(i);
			
			executeCompositeOperations(operations);
		} catch (Exception e) {}
		finally { if (fileReader != null) fileReader.close(); }
	}
	
	//ADD, SUB, INVSUB, MUL, DIV, INVDIV, POW, LOG, ABS, MIN, MAXIM, INV, GRAY, BNW, MED, COMP
	public void executeCompositeOperations(int [] operations) {
		for (int i=0; i<operations.length; i++) {
			switch(operations[i]) {
			case 0: //add
				executeOperationD(OperationType.ADD);
				break;
			case 1: //add
				executeOperationD(OperationType.SUB);
				break;
			case 2: //add
				executeOperationD(OperationType.INVSUB);
				break;
			case 3: //add
				executeOperationD(OperationType.MUL);
				break;
			case 4: //add
				executeOperationD(OperationType.DIV);
				break;
			case 5: //add
				executeOperationD(OperationType.INVDIV);
				break;
			case 6: //add
				executeOperationD(OperationType.POW);
				break;
			case 7: //add
				executeOperationD(OperationType.LOG);
				break;
			case 8: //add
				executeOperationD(OperationType.ABS);
				break;
			case 9: //add
				executeOperationD(OperationType.MIN);
				break;
			case 10: //add
				executeOperationD(OperationType.MAXIM);
				break;
			case 11: //add
				executeOperationD(OperationType.INV);
				break;
			case 12: //add
				executeOperationD(OperationType.GRAY);
				break;
			case 13: //add
				executeOperationD(OperationType.BNW);
				break;
			case 14: //add
				executeOperationD(OperationType.MED);
				break;
			}
		}
	}
	
	private void executeOperationD(OperationType type) {
		if(type == OperationType.ADD || type == OperationType.SUB || 
				   type == OperationType.INVSUB || type == OperationType.MUL || 
				   type == OperationType.DIV || type == OperationType.INVDIV || 
			       type == OperationType.POW || type == OperationType.MIN || 
			       type == OperationType.MAXIM) {
			String result = showInputDialog("" + type);
	        if(result != null && result.length() > 0) {
	        	try {
	        		int value = Integer.parseInt(result);
		            imageCanvas.addBasicOperation(type, value, false, false, false);
					imageCanvas.executeBasicOperation();
					imageCanvas.repaint();
	        	} catch (NumberFormatException ex) {}
	        }
		} else { //ne treba numericki parametar
			imageCanvas.addBasicOperation(type, 0, false, false, false);
			imageCanvas.executeBasicOperation();
			imageCanvas.repaint();
		}
	}
	
	public Main() {
		//width = 400;
		//height = 400;
		//mat = generateRandomImage(width, height);
		
		//experimental
		System.setProperty("sun.awt.noerasebackground", "true");
		
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				dispose();
			}
		});		
		
		MenuBar menuBar = new MenuBar();
		
		Menu fileMenu = new Menu("File");
		fileMenu.addActionListener(menuListener);
		
		fileMenu.add("Open");
		Menu saveAs = new Menu("SaveAs");
		saveAs.addActionListener(menuListener);
		fileMenu.add(saveAs);
		saveAs.add("BMP");
		saveAs.add("PAM");
		saveAs.add("PersonalFormat");
		fileMenu.add("Exit");
		
		Menu editMenu = new Menu("Edit");
		editMenu.addActionListener(menuListener);
		
		Menu sel = new Menu("Selections");
		sel.addActionListener(menuListener);
		editMenu.add(sel);
		sel.add("AddSelection");
		sel.add("SelectMainSelection");
		sel.add("DeleteMainSelection");
		sel.add("FillWithColour");
		
		Menu basicOp = new Menu("BasicOperations");
		basicOp.addActionListener(menuListener);
		editMenu.add(basicOp);
		//ADD, SUB, INVSUB, MUL, DIV, INVDIV, POW, LOG, ABS, MIN, MAXIM, INV, GRAY, BNW, MED, COMP
		basicOp.add("ADD");
		basicOp.add("SUB");
		basicOp.add("INVSUB");
		basicOp.add("MUL");
		basicOp.add("DIV");
		basicOp.add("INVDIV");
		basicOp.add("POW");
		basicOp.add("LOG");
		basicOp.add("ABS");
		basicOp.add("MIN");
		basicOp.add("MAXIM");
		basicOp.add("INV");
		basicOp.add("GRAY");
		basicOp.add("BNW");
		basicOp.add("MED");
		basicOp.add("COMP");
		
		editMenu.add("CompositeOperations"); //Napravi dijalog za stikliranje operacija zeljenih
		
		/*
		 * editMenu.add("Selections"); editMenu.add("BasicOperations");
		 * editMenu.add("CompositeOperations");
		 */
		Menu layersMenu = new Menu("Layers");
		layersMenu.addActionListener(menuListener);
		
		layersMenu.add("AddNewLayer");
		layersMenu.add("UpdateMainLayer");
		layersMenu.add("DeleteMainLayer");
		layersMenu.add("SelectMainLayer");
		layersMenu.add("ShowNames");
		
		Menu rectangleMenu = new Menu("Rectangles");
		rectangleMenu.addActionListener(menuListener);
		
		rectangleMenu.add("AddNewRectangle");
		rectangleMenu.add("DeleteRectangle");//moram da updateujem sve AKTIVAN(SELEKTOVAN) za layere, sliku
		
		
		menuBar.add(fileMenu);
		menuBar.add(editMenu);
		menuBar.add(layersMenu);
		menuBar.add(rectangleMenu);
		
		
		setMenuBar(menuBar);		
		
		imageCanvas = new ImageCanvas(this);
		imageCanvas.addMouseListener(canvasMouseListener);
		add(imageCanvas, BorderLayout.CENTER);
		
		imageCanvas.addSelection(new Selection("main"));
		
		//imageCanvas.drawImage(mat, width, height);
		
		/*toolbar = new Panel();
		toolbar.setLayout(new GridLayout(0, 2));
		Button command1 = new Button("C");
		command1.addActionListener(toolbarListener);
		toolbar.add(command1);
		Button command2 = new Button("A");
		command2.addActionListener(toolbarListener);
		toolbar.add(command2);
		Button command3 = new Button("T");
		command3.addActionListener(toolbarListener);
		toolbar.add(command3);
		Button command4 = new Button("G");
		command4.addActionListener(toolbarListener);
		toolbar.add(command4);
		Button command5 = new Button("M");
		command5.addActionListener(toolbarListener);
		toolbar.add(command5);
		Button command6 = new Button("P");
		command6.addActionListener(toolbarListener);
		toolbar.add(command6);
		Button command7 = new Button("X");
		command7.addActionListener(toolbarListener);
		toolbar.add(command7);
		Button command8 = new Button("Y");
		command8.addActionListener(toolbarListener);
		toolbar.add(command8);
		add(toolbar, BorderLayout.WEST);*/
		
		setTitle("POOP");
		setBounds(100, 100, FRAME_WIDTH, FRAME_HEIGHT);
		setResizable(false); //probacu sa TRUE, mzd mora namestanje slike i slicno, ili repaint, revalidate...
		setVisible(true);
	}
	
	public static void main(String [] args) {
		new Main();
	}
}
