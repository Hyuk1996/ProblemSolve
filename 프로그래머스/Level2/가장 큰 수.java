import static java.util.Comparator.*;
import static java.util.stream.Collectors.*;

import java.util.Arrays;

public class Solution {
	public String solution(int[] numbers) {
        if (isZero(numbers)) {
            return "0";
        }
        
		return Arrays.stream(numbers).mapToObj(String::valueOf)
			.sorted((s1, s2) -> compareString(s1, s2))
			.collect(joining());
	}
    
    private boolean isZero(int[] numbers) {
        for (int number : numbers) {
            if (number != 0) {
                return false;
            }
        }
        return true;
    }
    
    private int compareString(String s1, String s2) {
        StringBuilder sb1 = new StringBuilder();
        sb1.append(s1).append(s2);
        
        StringBuilder sb2 = new StringBuilder();
        sb2.append(s2).append(s1);
        
        return sb2.compareTo(sb1);
    }
}
