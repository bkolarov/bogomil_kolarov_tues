package elsys.org.greenBelt.src;

public class BarChart extends Chart implements IvanPetrov {

	
	
	
	public BarChart(int value1, int value2) {
		super(value1, value2);
	}

	@Override
	public void ivan() {
		this.value2 = value1*2;
	}

}
