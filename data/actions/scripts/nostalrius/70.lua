function onUse(player, item, fromPosition, target, toPosition)
	if player:getStorageValue(287) == 1 then
		player:setStorageValue(287, 2)
		 Game.createItem(3233, 1, player:getPosition())
		 Game.sendMagicEffect(item:getPosition(), 2)
	end
	return true
end