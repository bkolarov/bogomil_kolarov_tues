package elsys.org.greenBelt.src;

public class PieChart extends Chart implements IvanPetrov {

	public PieChart(int value1, int value2, int value3) {
		super(value1, value2, value3);
	}

	@Override
	public void ivan() {
		this.value2 -= value1;
	}

}
