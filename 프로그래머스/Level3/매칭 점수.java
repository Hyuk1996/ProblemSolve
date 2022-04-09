import java.util.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

class Solution {
    
    Map<String, Integer> pageIndex;
    double[] basicScore;
    List<String>[] linkUrlList;
    
    public int solution(String word, String[] pages) {
        
        pageIndex = new HashMap<>();
        basicScore = new double[pages.length];
        linkUrlList = new List[pages.length];
        initLinkUrlList();
        
        parsingHtmls(word, pages);        
        
        double[] totalScore = calTotalScore();
    
        return getMaxScoreIndex(totalScore);
    }
    
    void initLinkUrlList() {
        for(int i = 0; i < linkUrlList.length; ++i) {
            linkUrlList[i] = new ArrayList<>();
        }
    }
    
    void parsingHtmls(String word, String[] pages) {
        Pattern homeUrlPattern = Pattern.compile("<meta property=\"og:url\" content=\"(\\S*)\"");
        Pattern urlPattern = Pattern.compile("<a href=\"https://(\\S*)\"");
        Pattern wordPattern = Pattern.compile("\\b(?i)" + word + "\\b");
        Matcher urlMatcher, wordMatcher, homeUrlMatcher;
        
        String homeUrl;
        String body;
        String linkUrl;
        
        for(int i = 0; i < pages.length; ++i) {
            
            //parsing home url
            homeUrlMatcher = homeUrlPattern.matcher(pages[i]);
            if(homeUrlMatcher.find()) {
                homeUrl = homeUrlMatcher.group().split("=")[2].replaceAll("\"","");
                pageIndex.put(homeUrl, i);
            }
            
            //parsing link url
            urlMatcher = urlPattern.matcher(pages[i]);
            while(urlMatcher.find()) {
                linkUrl = urlMatcher.group().split("\"")[1];
                linkUrlList[i].add(linkUrl);
            }
            
            //parsing word count
            body = pages[i].split("<body>")[1].split("</body>")[0].replaceAll("[0-9]", " ");
            wordMatcher = wordPattern.matcher(body);
            int word_cnt = 0;
            while(wordMatcher.find()) {
                word_cnt++;
            }
            basicScore[i] = word_cnt;
        }
    }
    
    double[] calTotalScore() {
        double[] totalScore = new double[basicScore.length];
        for(int i = 0; i < totalScore.length; ++i) {
            totalScore[i] = basicScore[i];
        }
        
        //외부 점수 계산
        for(int i = 0; i < totalScore.length; ++i) {
            if(linkUrlList[i].size() == 0) {
                continue;
            }
            
            double score = basicScore[i] / (double) linkUrlList[i].size();
            for(String url : linkUrlList[i]) {
                if(pageIndex.containsKey(url)) {
                    totalScore[pageIndex.get(url)] += score;
                }
            }
        }
        return totalScore;
    }
    
    int getMaxScoreIndex(double[] totalScore) {
        double max = totalScore[0];
        int answer = 0;
        for(int i = 1; i < totalScore.length; ++i) {
            if(max < totalScore[i]) {
                max = totalScore[i];
                answer = i;
            }
        }
        return answer;
    }
    
}
