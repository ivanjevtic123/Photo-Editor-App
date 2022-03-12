package poop;

import java.util.ArrayList;

public class Selection {


	private String name;
	ArrayList<Rectangle> rectangles = new ArrayList<Rectangle>();
	
	
	
	public Selection(String nn/*, vector<Rectangle *> rr*/) {//nakon svakog puta: updateSelecton();
		this.name = nn;
		//rectangles = rr; //deep cpy of pointers, shallow cpy of objects, taking control of pointed objects
		//updateSelection();//prodji kroz sliku po formuli
	}

	public String getName() {
		return name;
	}

	//setujem RGB
	public void fillWithColour(Layer layer, int r, int g, int b) {
		for (int i = 0; i < (layer.getH()); i++) {
			for (int j = 0; j < (layer.getW()); j++) {//umesto j sam pisao i, bravo 
				if (layer.matrix[i][j].getActive()) {
					layer.matrix[i][j].setR(r);
					layer.matrix[i][j].setG(g);
					layer.matrix[i][j].setB(b);
				}
			}
		}
	}

	//============================================================================================
	//!!!SVE RADI OKO DODAVANJA!!!
	void createAndAddRectangle(int x, int y, int w, int h, Layer layer, Operation opBasic, CompositeOperation opComposite) {
		Rectangle r = new Rectangle(x, y, w, h);
		addRectangle(r);
		//sad update:
		updateSelection(layer, r, opBasic, opComposite);
	}
	public void addRectangle(Rectangle r) {//nakon svakog puta: updateSelecton();
		rectangles.add(r);
		//updateSelection();//prodji kroz sliku po formuli
	}
	
	public void updateSelection(Layer layer, Rectangle r, Operation opBasic, CompositeOperation opComposite) { 
		/*int pomX = 0, pomY = 0, pomHeight = 0, pomWidth = 0;
		boolean flagBadSelection = false;

		if (r.getX() < 0) pomX = 0;
		else if (r.getX() > layer.getH()) flagBadSelection = true; //pomX = layer->getHeight();//lose
		else pomX = r.getX();

		if (r.getY() < 0) pomY = 0;
		else if (r.getY() > layer.getW()) flagBadSelection = true;//pomY = layer->getWidth();
		else pomY = r.getY();
		
		if (r.getHeight() < 0) pomHeight = 0;
		else if (r.getHeight() + pomX > layer.getH()) pomHeight = layer.getH() - pomX;//pomHeight = layer->getHeight();
		else pomHeight = r.getHeight();

		if (r.getWidth() < 0) pomWidth = 0;
		else if (r.getWidth() + pomY > layer.getW()) pomWidth = layer.getW()  - pomY;//pomWidth = layer->getWidth();
		else pomWidth = r.getWidth();

		if (flagBadSelection == true) {
			System.out.println("Lose dimenzije rectanglea!");//sipis GUI TREBA!!!
			return;
		}

		for (int i = pomX; i < pomX + pomHeight; i++) {
			for (int j = pomY; j < pomY + pomWidth; j++) {
				if(layer.matrix[i][j] != null)layer.matrix[i][j].setActive(r.getStatus());//BUG!!!!!
			}
		}
		if(opBasic != null) opBasic.setSelectionExists(true);//ispod stavi
		if (opComposite != null) opComposite.setSelectionExists(true);//ispod for stavi
		*/
		
	}
	/*void updateSelection(Layer *layer, Rectangle *r, Operation *opBasic, CompositeOperation *opComposite) {
		for (int i = 0; i < layer->getHeight(); i++) {
			for (int j = 0; j < layer->getWidth(); j++) {

			}
		}

	}*/

	//============================================================================================
	

	//SVE DELOVE SELEKCIJE UPDATEUJE
	//pri brisanju rectangla jednog, tad zovi
	public void updateWithAllRectangles(Layer layer, Operation opBasic, CompositeOperation opComposite) {
		for (int i = 0; i < rectangles.size(); i++) {
			updateSelection(layer, rectangles.get(i), opBasic, opComposite);//BUG!!!
		}
	}

	//obavezno updateSelection(...) nakon ove fje:
	public void deleteRectangle(int index) {//od 0 do n
		rectangles.remove(index);
	}

	public void destroySelection(Layer layer, Operation opBasic, CompositeOperation opComposite) {//samo da se poziva na mainSelection; ako izaberem drugi selection za
		rectangles.clear();  //main, onda opet postaviti SelectionExists na true!!!
		if (opBasic != null) opBasic.setSelectionExists(false);
		if (opComposite != null) opComposite.setSelectionExists(false);
		//prodji kroz ceo matrix
		for (int i = 0; i < layer.getH(); i++) {
			for (int j = 0; j < layer.getW(); j++) {
				layer.matrix[i][j].setActive(false);
			}
		}
	}

	
	
	
	
}
