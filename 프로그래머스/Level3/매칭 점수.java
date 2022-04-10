import java.util.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

class Solution {
        
    int pageCnt;
    Map<String, Integer> index;
    double[] basicScore;
    List<String>[] linkList;
    
    public int solution(String word, String[] pages) {
        
        this.pageCnt = pages.length;
        
        index = new HashMap<>();
        basicScore = new double[pageCnt];
        linkList = new List[pageCnt];        
        
        parsingHtmls(word, pages);
        
        double[] totalScore = getTotalScore();
      
        return maxScorePageIndex(totalScore);
    }
    
    void parsingHtmls(String word, String[] pages) {
        
        Pattern homeUrlPattern = Pattern.compile("<meta property=\"og:url\" content=\"(\\S*)\"");
        Pattern linkUrlPattern = Pattern.compile("<a href=\"(\\S*)\"");
        Pattern wordPattern = Pattern.compile("\\b(?i)" + word + "\\b");
        
        for(int i = 0; i < pageCnt; ++i) {
            //parsing home url
            Matcher homeUrlMatcher = homeUrlPattern.matcher(pages[i]);
            if(homeUrlMatcher.find()) {
                index.put(homeUrlMatcher.group().split("=")[2].replaceAll("\"", ""), i);
            }
            
            //parsing link url
            Matcher linkUrlMatcher = linkUrlPattern.matcher(pages[i]);
            linkList[i] = new ArrayList<>();
            while(linkUrlMatcher.find()) {
                linkList[i].add(linkUrlMatcher.group().split("=")[1].replaceAll("\"", ""));
            }
            
            String text = pages[i].replaceAll("<[^>]*>", "").replaceAll("[0-9]", " ");
            Matcher wordMatcher = wordPattern.matcher(text);
            int wordCnt = 0;
            while(wordMatcher.find()) {
                wordCnt++;
            }
            basicScore[i] = (double) wordCnt;            
        }
    }
    
    double[] getTotalScore() {
        double[] totalScore = new double[pageCnt];
        for(int i = 0; i < pageCnt; ++i) {
            totalScore[i] += basicScore[i];

            for(String url : linkList[i]) {
                if(index.containsKey(url)) {
                    totalScore[index.get(url)] += (basicScore[i] / (double) linkList[i].size());
                }
            }
        }
        return totalScore;
    }
    
    int maxScorePageIndex(double[] totalScore) {
        double max = totalScore[0];
        int answer = 0;
        for(int i = 1; i < pageCnt; ++i) {
            if(max < totalScore[i]) {
                max = totalScore[i];
                answer = i;
            }
        }
        return answer;
    }
    
}
