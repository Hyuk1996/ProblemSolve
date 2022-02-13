import java.util.*;

class Solution {
    public String[] solution(String[] files) {
      
        List<File> fileList = new ArrayList<>();
        for(String file : files) {
            fileList.add(new File(file));
        }
        
        Collections.sort(fileList);
        
        String[] answer = new String[fileList.size()];
        for(int i = 0; i < fileList.size(); ++i) {
            answer[i] = fileList.get(i).fileName;
        }
        
        return answer;
    }
    
    static class File implements Comparable<File>{
        String fileName;
        String HEAD;
        Integer NUMBER;
        
        File(String fileName) {
            this.fileName = fileName;
            
            //HEAD, NUMBER 부분으로 쪼개기
            splitFileName();
        }
        
        void splitFileName() {
            int idx = 0;
            for(int i = 0; i < fileName.length(); ++i) {
                if(Character.isDigit(fileName.charAt(i))) {
                    idx = i;
                    break;
                }
            }
            HEAD = fileName.substring(0, idx).toLowerCase();
            
            int idx2 = idx;
            for(int i = idx; i < fileName.length(); ++i) {
                if(!Character.isDigit(fileName.charAt(i))) {
                    break;
                }
                idx2++;
            }
            NUMBER = Integer.parseInt(fileName.substring(idx, idx2));
        }
        
        public int compareTo(File f) {
            if(this.HEAD.equals(f.HEAD)) {
                return this.NUMBER - f.NUMBER;
            } else {
                return this.HEAD.compareTo(f.HEAD);
            }
        }
    }
}
