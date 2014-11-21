import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;

public class CLOOK {
	private int h = 0;
	private ArrayList<Integer> r;
	private ArrayList<Integer> tmp = new ArrayList<Integer>();

	public CLOOK(int head, ArrayList<Integer> requests) {
		h = head;
		r = new ArrayList<Integer>(requests);
	}

	public void run() {
		this.r.add(0, this.h);
		
		Collections.sort(this.r);
		Iterator<Integer> itr = this.r.iterator();
		while (itr.hasNext()) {
			Integer x = itr.next();
			if (x < this.h){
				itr.remove();
				tmp.add(x);
			}
		}
		
		for (Integer x: tmp) {
			this.r.add(x);
		}
		
		display();
	}
	
	private void display() {
		int tmp = 0;
		int cnt = 0;
		int total = 0;
		
		System.out.print("Disk head pos: ");
		
		for (Integer x: this.r) {
			if (cnt == 0) {
				System.out.print(x + " -> ");
				tmp = x;
				cnt++;
			} else if (cnt != this.r.size() - 1) {
				System.out.print(x + " -> ");
				cnt++;
				total = total + Math.abs(x - tmp);
				tmp = x;
			} else {
				System.out.print(x);
				total = total + Math.abs(x - tmp);
			}
		}
		
		System.out.println();
		System.out.println("Total head movement: " + total);
	}

}
