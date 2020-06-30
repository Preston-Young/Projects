class Player:
    STARTINGFUNDS = 1000

    def __init__(self, name):
        self.name = name
        self.money = self.STARTINGFUNDS
        self.wager = 0
        self.insuranceWager = 0
        self.hand = [[]]
        self.totalScore = [0]
        self.turn = False

    # Returns player name
    def getName(self) -> str:
        return self.name

    # Returns player money
    def getMoney(self) -> int:
        return self.money

    # Sets the player's wager
    def setWager(self, wager: int) -> None:
        self.wager = wager

    # Returns player wager
    def getWager(self) -> int:
        return self.wager

    # Sets the player's insurance wager
    def setInsuranceWager(self, wager: int) -> None:
        self.insuranceWager = wager

    # Returns player insurance wager
    def getInsuranceWager(self) -> int:
        return self.insuranceWager

    # Returns the player's hand(s) (hands if player chose to split)
    def getHand(self, hand_num: int = 1) -> [str]:
        return self.hand[hand_num-1]

    # Sets the total score of the player's hand(s) (hands if player chose to split)
    def setTotalScore(self, score: int, hand_num: int = 1) -> None:
        self.totalScore[hand_num-1] = score

    # Returns total score of player's hand(s) (hands if player chose to split)
    def getTotalScore(self, hand_num: int = 1) -> int:
        return self.totalScore[hand_num-1]

    # Returns size of player's hand(s) (hands if player chose to split)
    def handSize(self, hand_num: int = 1) -> int:
        return len(self.hand[hand_num-1])

    # Sets the player's turn to true or false
    def setTurn(self, is_turn: bool) -> None:
        self.turn = is_turn

    # Returns whether or not it's the player's turn
    def isTurn(self) -> bool:
        return self.turn

    # Adds a card to player's hand(s) (hands if player chose to split)
    def addCard(self, card: str, hand_num: int = 1) -> None:
        self.hand[hand_num-1].append(card)

    # Adds winnings (or subtracts losings) to player's total money
    def addMoney(self, money) -> None:
        self.money += money

    # Player can split into two hands if both original cards have identical values
    def split(self) -> None:
        card = self.hand[0].pop(0)
        self.hand.append([card])
        self.wager *= 2

    # Player can double down when original two cards total up to 9, 10, or 11
    def doubleDown(self) -> None:
        self.wager *= 2

    # A player can place a side insurance bet up to half of their original wager that
    # the dealer will have a "blackjack." If the dealer indeed has a "blackjack," the
    # player will receive twice the amount they wagered for this side bet and their
    # original wager gets treated under the normal BlackJack rules. Players only get the
    # option to make this bet if the dealer's face-up card is specifically an Ace.
    def insurance(self, wager: int) -> None:
        self.insuranceWager = wager

    # Returns the preset starting funds
    def getStartingFunds(self) -> int:
        return self.STARTINGFUNDS

    # Resets the necessary attributes after the round is over
    def resetPlayer(self) -> None:
        self.wager = 0
        self.insuranceWager = 0
        self.hand = [[]]
        self.totalScore = [0]
