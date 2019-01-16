function onUse(player, item, fromPosition, target, toPosition)
	if player:getItemCount(3231) >= 1 and player:getStorageValue(283) == 1 then
		Game.sendMagicEffect({x = 33048, y = 32630, z = 01}, 14)
		player:removeItem(3231, 1)
		Game.createItem(3243, 1, {x = 33048, y = 32631, z = 01})
		player:setStorageValue(283, 2)
	end
	return true
end