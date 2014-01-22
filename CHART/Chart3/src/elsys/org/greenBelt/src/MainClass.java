package elsys.org.greenBelt.src;

import java.util.ArrayList;
import java.util.Scanner;

public class MainClass {

	public static void main(String[] args) {
		int value;
		
		ArrayList<Chart> list = new ArrayList<Chart>();
		Scanner terminal = new Scanner(System.in);
		
		String text;
		
		int loopCount = 0;
		
		while(true) {
			text = terminal.next();
			System.out.println(text);
			if(text.equals("a")) {
				break;
			}
			
			value = Integer.parseInt(text);
			
			if(loopCount % 2 == 0) {
				PieChart p = new PieChart(value*2, value*4);
				list.add(p);
			}else {
				BarChart b = new BarChart(value*3, value*5);
				list.add(b);
			}
			
			++loopCount;
		}
		
		for(Chart ch: list) {
			System.out.println(ch.value1);
			System.out.println(ch.value2);
			
			if(ch instanceof BarChart) {
				((BarChart)ch).ivan();
			}
		}
		
		for(Chart ch: list) {
			if(ch instanceof BarChart) {
				System.out.println(((BarChart)ch).value1 + ((BarChart)ch).value2);
			}else {
				System.out.println(((PieChart)ch).value1 + ((BarChart)ch).value2);
			}
		}
		
	}

}