package poop;


//
//ADD, SUB, INVSUB, MUL, DIV, INVDIV, POW, LOG, ABS, MIN, MAXIM, INV, GRAY, BNW, MED, COMP
public abstract class Operation {

	public enum OperationType { ADD, SUB, INVSUB, MUL, DIV, INVDIV, POW, LOG, ABS, MIN, MAXIM, INV, GRAY, BNW, MED, COMP };
	//basic operation da sadrzi operationType
	protected  boolean selectionExists;
	
	


	public Operation(boolean flag) {
		this.selectionExists = flag;
	}
	public Operation() {
		this(false);
	}

	public void setSelectionExists(boolean flag) { //setuj ga pri prvoj selekciji, unsetuj pri brijsanju selekcije(ako bude brisanja)
		selectionExists = flag; 
	}

	public boolean getSelectionExists() {
		return selectionExists;
	}

	public abstract void execution(Pixel curr);

	public abstract void setLastFlag(boolean flag);

	public abstract OperationType getOperationType();

	public abstract int getNum();
	
}



	