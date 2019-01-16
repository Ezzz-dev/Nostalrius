function canJoin(player)
	return player:getAccountType() >= ACCOUNT_TYPE_GAMEMASTER
end
