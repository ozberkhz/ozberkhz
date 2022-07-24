class GameStats:
    """Track statistics for Alien Invasion"""

    def __init__(self, ai_game):
        """Inıtialize statistics"""
        self.settings = ai_game.settings

        # Highscore should never be reset
        try:
            with open('highscore.txt') as highscore_file:
                for line in highscore_file:
                    self.high_score = int(line)
        except:
            with open('highscore.txt', 'w') as highscore_file:
                highscore_file.write('0')
                self.high_score = 0

        self.reset_stats()

        # Start Alien Invasion in an active state
        self.game_active = False

    def reset_stats(self):
        """Initialize statistics that can change during the game"""
        self.ships_left = self.settings.ship_limit
        self.score = 0
        self.level = 1