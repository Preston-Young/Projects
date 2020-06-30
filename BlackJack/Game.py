from Player import Player
from Dealer import Dealer
from Cards import Cards
from Scoring import Scoring

class Game:

    # Constants for min bet, max bet, payout, and when to shuffle
    MINBET = 20
    MAXBET = 500
    BLACKJACKPAYOUTSTR = '3:2'
    BLACKJACKPAYOUT = int(BLACKJACKPAYOUTSTR.split(':')[0]) / int(BLACKJACKPAYOUTSTR.split(':')[1])
    DEALER = Dealer()
    CARDS = Cards()
    SCORING = Scoring()
    WHENTOSHUFFLE = (CARDS.getNumDecks() * 52) // 3
    # WHENTOSHUFFLE is a const int that indicates how many cards need to be left before reshuffling the deck

    def __init__(self):
        self.players = []
        self.roundOver = True
        self.winnings = []

    # Add a player to the game, but only after the round is over
    def addPlayer(self, player: Player) -> None:
        if self.roundOver:
            self.players.append(player)

    # Removes a player from the game. Player is allowed to leave before
    # round is over, but they'll lose their wager.
    def removePlayer(self, player: Player) -> None:
        if player in self.players:
            self.players.remove(player)

    # Returns the current number of players
    def getNumPlayers(self) -> int:
        return len(self.players)

    # Returns a bool indicating whether the round is over or not
    def isRoundOver(self) -> bool:
        return self.roundOver

    # Uses the Scoring class to compare the player's hand to the dealer's
    # hand. Based on the winnter and whether each person has a BlackJack,
    # the winnings (or losings) are determined for the player based on their
    # hand and their wager
    def determineWinnings(self) -> None:
        dealer_hand = self.DEALER.getHand()
        dealer_score = self.DEALER.getTotalScore()
        print('~~~~~~~~~~~~~~~Final Standings~~~~~~~~~~~~~~~')
        print(f'Dealer\'s final hand: {dealer_hand} === {dealer_score} points')
        breakpoint = input('')

        for player in self.players:
            wager = player.getWager()
            insurance_wager = player.getInsuranceWager()
            player_hand = player.getHand()
            player_score = player.getTotalScore()

            # If dealer gets a BlackJack, the player loses their wager unless they also have a BlackJack.
            # Also, they win twice their insurance wager if they chose to make one at the beginning of the round.
            if dealer_score == 21 and self.DEALER.handSize() == 2:
                if player_score == 21 and player.handSize() == 2:
                    winning = 0 + (insurance_wager * 2)
                else:
                    winning = (wager * -1) + (insurance_wager * 2)

            # Payout for a BlackJack is based on the preset amount
            elif player_score == 21 and player.handSize() == 2:
                winning = int(wager * self.BLACKJACKPAYOUT) + (insurance_wager * -1)

            # If player busts, they lose their wager regardless of what hand the dealer has (even if the dealer busts)
            elif player_score > 21:
                winning = (wager * -1) + (insurance_wager * -1)

            # If the dealer busts or the player has a higher score than the dealer, they win their wager back
            elif dealer_score > 21 or player_score > dealer_score:
                winning = wager + (insurance_wager * -1)

            # If neither the player nor dealer busts, but the player has a lower score than the dealer,
            # the player loses their wager.
            elif player_score < dealer_score:
                winning = (wager * -1) + (insurance_wager * -1)

            # The last case is where the player has the same score as the dealer.
            else:
                winning = 0 + (insurance_wager * -1)

            print(f'{player.getName()}\'s hand: {player_hand} === {player_score} points | Winnings: {winning}')
            self.winnings.append((player, winning))
            breakpoint = input('')
        self.distributeWinnings()

    # Distributes all the winnings (or losings) back to the players and
    # changes their total money accordingly
    def distributeWinnings(self) -> None:
        for player, money in self.winnings:
            player.addMoney(money)

        # Kick a player out of the round if they're out of money
        for player in self.players[:]:
            if player.getMoney() <= 0:
                print(f'Sorry, {player.getName()}! You\'re out of money :( Thanks for playing!')
                self.removePlayer(player)
                breakpoint = input('')

        self.endRound()

    # Starts a new round and asks each player to make a wager before the cards are dealt.
    # New players are not allowed to join until the round is over.
    # Also, a round can't be started if there's no players in the game yet.
    def newRound(self) -> None:
        self.roundOver = False

        print()
        print('~~~~~~~~~~Welcome Challengers!~~~~~~~~~~')
        print(f'For this round we\'re using {self.CARDS.getNumDecks()} full decks and we have {len(self.players)} challengers playing.')
        print(f'The current number of cards left in the deck is {self.CARDS.deckSize()}')
        print(f'The deck will be reshuffled after {self.CARDS.deckSize() - self.WHENTOSHUFFLE} more cards are drawn')

        # For each player, ask them to make a wager
        for player in self.players:
            player_money = player.getMoney()
            wager_is_int = False

            print()
            print(f'Player: {player.getName()}')
            print(f'Total Money: ${player_money}')

            # Accounting for user error of inputting anything other than an int for the wager.
            while not wager_is_int:
                try:
                    # Covering the edge case of a player have less money left than the minimum bet.
                    if player_money < self.MINBET:
                        print()
                        print(f'Since you currently have less money than the minimum bet (${self.MINBET}), you\'ll have to bet all your money!')
                        breakpoint = input('')
                        wager = player_money

                    # Makes sure player bets within the range of the preset min and max bet.
                    # Also, the player must have enough money left to make the bet.
                    else:
                        wager = int( input(f'Please make a wager from ${self.MINBET} to ${self.MAXBET}: ') )
                        while (wager < self.MINBET) or (wager > self.MAXBET) or (wager > player_money):
                            if wager < self.MINBET:
                                print(f'Sorry, you must bet at least ${self.MINBET}.')
                            elif wager > self.MAXBET:
                                print(f'Sorry, you can\'t bet more than ${self.MAXBET}.')
                            elif wager > player_money:
                                print('You don\'t have enough money to make that bet!')
                            print()
                            wager = int(input(f'Please make a wager from ${self.MINBET} to ${self.MAXBET}: '))
                    wager_is_int = True

                except ValueError:
                    print('Must give an int for your wager.')
                    print()

            player.setWager(wager)

        print()
        print('~~~~~~~~~~Let the round begin. Good luck!~~~~~~~~~~')
        print()
        self.dealInitialCards()

    # Ends the round, clearing all of the hands and previous winnings
    def endRound(self) -> None:
        self.roundOver = True
        self.winnings = []

        # Shuffles the cards if necessary
        if self.CARDS.deckSize() <= self.WHENTOSHUFFLE:
            self.CARDS.shuffle()
            print('Shuffling cards...')
            breakpoint = input('')

        # Accounts for edge case that all the players lose their money and get kicked out of the game
        if self.getNumPlayers() > 0:
            print('~~~~~~~~~~~~~~~Everyone\'s Total Money~~~~~~~~~~~~~~~')
            for player in self.players:
                player.resetPlayer()
                print(f'{player.getName()}: ${player.getMoney()}')
        else:
            print('There\'s no more players left! Everyone ran out of money :(')

        self.DEALER.resetDealer()

        print()
        print('The round is over! Good game everyone!')
        breakpoint = input('')

    # Deals two cards to each player and then the dealer. Note that one
    # card is dealt to everyone before the second card is dealt.
    # I added 'breakpoint' variables for now to simulate dealing one card at a time.
    def dealInitialCards(self) -> None:
        for player in self.players:
            player.addCard(self.CARDS.getCard())
            print(f'{player.getName()}\'s hand: {player.getHand()} === {self.SCORING.totalScore(player.getHand())} points')
            breakpoint = input('')

        self.DEALER.addCard(self.CARDS.getCard())
        dealer_hand = self.DEALER.getHand()
        print(f'Dealer\'s hand: {dealer_hand} === {self.SCORING.totalScore(dealer_hand)} points')
        breakpoint = input('')

        # All players have the option of making an insurance bet only if the dealer's first card is an Ace.
        if dealer_hand[0][0] == 'A':
            for player in self.players:
                insurance = input(f'{player.getName()}, care to make an insurance bet? (Y/N) ')
                while (insurance.upper() != 'Y') and (insurance.upper() != 'N'):
                    insurance = input(f'{player.getName()}, care to make an insurance bet? (Y/N) ')

                if insurance.upper() == 'Y':
                    insurance_wager_is_int = False
                    print()

                    # Accounting for user error of inputting anything other than an int for the wager.
                    while not insurance_wager_is_int:
                        try:
                            insurance_wager = int(input(f'Please make an insurance wager from $1 to ${player.getWager()//2} '))
                            while (insurance_wager < 1) or (insurance_wager > player.getWager()//2) or (player.getMoney() - insurance_wager < 0):
                                if insurance_wager < 1:
                                    print('Sorry, you can\'t wager anything less than $1.')
                                elif insurance_wager > player.getWager()//2:
                                    print(f'Sorry, you can\'t wager anything more than ${player.getWager()//2}.')
                                else:
                                    print('You don\'t have enough money to make that bet!')
                                print()
                                insurance_wager = int(input(f'Please make an insurance wager from $1 to ${player.getWager() // 2} '))
                            insurance_wager_is_int = True

                        except ValueError:
                            print('Insurance wager must be an int.')
                            print()
                    player.setInsuranceWager(insurance_wager)
                print()

        for player in self.players:
            player_card = self.CARDS.getCard()
            player.addCard(player_card)
            print(f'{player.getName()}\'s hand: {player.getHand()} === {self.SCORING.totalScore(player.getHand())} points')
            breakpoint = input('')

        dealer_card = self.CARDS.getCard()
        self.DEALER.addCard(dealer_card)
        dealer_hand = [self.DEALER.getHand()[0], '?']
        print(f'Dealer\'s hand: {dealer_hand} <= {self.SCORING.totalScore( [dealer_hand[0]] )} points')
        breakpoint = input('')

        self.dealPlayerCards()

    # Deals the rest of the cards to the players (depending on whether they choose
    # to hit or stand) and then to the dealer
    def dealPlayerCards(self) -> None:
        for player in self.players:
            print(f'~~~~~~~~~~~~~~~~{player.getName()}\'s Turn~~~~~~~~~~~~~~~~')
            print()

            player_hand = player.getHand()
            hand_score = self.SCORING.totalScore(player_hand)

            # Check to see if the player has a BlackJack. Otherwise, proceed with their turn.
            if hand_score == 21:
                print(f'Your hand: {player_hand} === {hand_score} points')
                print()
                print(f'Congrats, {player.getName()}! You got a BlackJack!')
                breakpoint = input('')
            else:
                player.setTurn(True)

            while player.isTurn():
                player_hand = player.getHand()
                hand_score = self.SCORING.totalScore(player_hand)
                print(f'Your hand: {player_hand} === {hand_score} points')
                print()

                if hand_score > 21:
                    print(f'Sorry, {player.getName()}, your hand is a bust!')
                    player.setTurn(False)
                    breakpoint = input('')

                else:
                    hit_or_stand = input('Would you like to hit or stand? ')

                    while (hit_or_stand.lower() != 'hit') and (hit_or_stand.lower() != 'stand'):
                        print('Must choose hit or stand.')
                        print()
                        hit_or_stand = input('Would you like to hit or stand? ')

                    if hit_or_stand.lower() == 'hit':
                        player.addCard(self.CARDS.getCard())
                    else:
                        player.setTurn(False)
                    print()
            player.setTotalScore(hand_score)
        self.dealDealerCards()

    # Dealer has their own set of rules for hitting and standing. Their decisions
    # are essentially made automatically: If the dealer's hand is 16 or less points, they
    # must hit. If their hand is 17 or more points, they must stand.
    def dealDealerCards(self) -> None:
        print('~~~~~~~~~~~~~~~~Dealer\'s Turn~~~~~~~~~~~~~~~~')
        print()

        dealer_hand = self.DEALER.getHand()
        dealer_score = self.SCORING.totalScore(dealer_hand)

        if dealer_score == 21:
            print(f'Dealer\'s hand: {dealer_hand} === {dealer_score}')
            print()
            print(f'The dealer got a BlackJack!')
            breakpoint = input('')
        else:
            self.DEALER.setTurn(True)

        while self.DEALER.isTurn():
            dealer_hand = self.DEALER.getHand()
            dealer_score = self.SCORING.totalScore(dealer_hand)
            print(f'Dealer\'s hand: {dealer_hand} === {dealer_score}')
            breakpoint = input('')

            if dealer_score > 21:
                print('The dealer\'s hand is a bust!')
                self.DEALER.setTurn(False)
            elif dealer_score <= 16:
                print('The dealer chose to hit.')
                self.DEALER.addCard(self.CARDS.getCard())
            else:
                print('The dealer chose to stand.')
                self.DEALER.setTurn(False)
            breakpoint = input('')

        self.DEALER.setTotalScore(dealer_score)
        self.determineWinnings()

    # Returns the list of players who had winning hands
    def getWinners(self) -> [Player]:
        return [player for player, winning in self.winnings if winning > 0]

    # Returns the preset minimum bet
    def getMinBet(self) -> int:
        return self.MINBET

    # Returns the preset maximum bet
    def getMaxBet(self) -> int:
        return self.MAXBET

    # Returns the preset payout for getting a BlackJack
    def getPayout(self) -> float:
        return self.BLACKJACKPAYOUT

    # Returns the present payout for getting a BlackJack as a str
    def getPayoutStr(self) -> str:
        return self.BLACKJACKPAYOUTSTR