package poop;

public class CompositeOperation extends Operation { 

	
	
	
	
	@Override
	public void execution(Pixel curr) { //jedan for, zvati native za svaki tip BasicOp
		
	}

	@Override
	public void setLastFlag(boolean flag) {
		
	}

	@Override
	public OperationType getOperationType() {
		return OperationType.COMP;
	}
	
	@Override
	public int getNum() {
		return 0;
	}

}
