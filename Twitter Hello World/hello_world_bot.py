import tweepy
import time

COSUMER_KEY = ""
CONSUMER_SECRET = ""
ACCESS_TOKEN = ""
ACCESS_TOKEN_SECRET = ""

# This is the text file, where I'll store the last seen tweet ID
LAST_SEEN_TWEETS_FILE_NAME = "Last Seen Tweets.txt"

auth = tweepy.OAuthHandler(COSUMER_KEY, CONSUMER_SECRET)
auth.set_access_token(ACCESS_TOKEN, ACCESS_TOKEN_SECRET)

api = tweepy.API(auth)

def storeTweetID(file_name: str, tweet_id: int) -> None:
    """
    Stores the last seen tweet ID in a text file.
    """
    with open(file_name, 'w') as last_seen_tweets:
        last_seen_tweets.write(str(tweet_id))

def retreiveTweetID(file_name: str) -> int:
    """
    Retreives the last seen tweet ID from the text file.
    """
    with open(file_name) as last_seen_tweets:
        return int(last_seen_tweets.read().strip())

def replyToTweets() -> None:
    """
    Parses the unseen mentioned tweets and replies back.
    """

    print('Parsing and replying to tweets...')

    # This makes sure I don't create duplicate replies to any tweet I've parsed through before.
    last_seen_Tweet_ID = retreiveTweetID(LAST_SEEN_TWEETS_FILE_NAME)
    mentions = api.mentions_timeline(last_seen_Tweet_ID)

    for tweet in reversed(mentions):
        print(f'@{tweet.user.screen_name} tweeted at you --- Tweet: {tweet.text}, {tweet.id}')
        
        for hashtag in tweet.entities['hashtags']:
            if hashtag['text'].lower() == 'helloworld':
                print(f'Replying to @{tweet.user.screen_name}...')
                api.update_status(f'@{tweet.user.screen_name} This is Preston\'s Twitter bot tweeting. Everything is working fine!', tweet.id)
                break
        
        storeTweetID(LAST_SEEN_TWEETS_FILE_NAME, tweet.id)

while True:
    replyToTweets()
    time.sleep(15)
