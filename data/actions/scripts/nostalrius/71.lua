function onUse(player, item, fromPosition, target, toPosition)
	if player:getItemCount(3231) >= 1 and player:getStorageValue(288) == 1 then
		Game.sendMagicEffect({x = 33094, y = 32524, z = 01}, 14)
		player:removeItem(3231, 1)
		Game.createItem(3243, 1, {x = 33095, y = 32524, z = 01})
		player:setStorageValue(288, 2)
	end
	return true
end