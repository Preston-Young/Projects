### This is a Twitter Bot I build in Python using the Twitter API
Using the API, my bot would parse through my user's "mentioned timeline," which is the collection of any tweets that tagged my account. For each tweet, if the original owner of the tweet used the hashtag #HelloWorld (not case sensitive, so #HelLOwoRLD would work too), my bot would automatically tweet a reply with a pre-written message that I choose. I hosted my bot on pythonanywhere.com, and using the time.sleep() method, my bot continuously checks every 15 seconds for any new tweets.

### What I liked about this project
Even though this was the smallest project I've built, I spent a lot of time learning the API, reading the documentation, and testing on my own to figure out what information I needed to extract. It was satisfying being able to build a bot that interacted with a technology that I use so frequently.

### What I want to implement in the future
In the future, I want to use my new familiarity with the Twitter API and integrate Google's Natural Language API. My idea is to look at all of the tweets under the top trending hashtags. By using machine learning and Google's Natural Language API, I plan to parse through all the tweets under each hashtag in order to generate the overall emotion for each one to display for the users.

## Here's a sample interaction of my bot running on pythonanywhere.com's cloud console
![Terminal Interaction](https://user-images.githubusercontent.com/56369636/87867725-d19e6800-c944-11ea-81cf-9257e134d089.JPG)

## Here's what an automated reply from my bot would look like
![Sample Tweet Reply](https://user-images.githubusercontent.com/56369636/87867730-e11db100-c944-11ea-8b55-a63719afee7d.JPG)

## Here are a few tweets where I mention my user, but notice that only the tweet containing the hashtag #HelloWorld received a reply from my bot
![Sample Tweets](https://user-images.githubusercontent.com/56369636/87867734-ebd84600-c944-11ea-80d1-49be6268e225.JPG)
