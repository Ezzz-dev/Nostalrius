function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		Game.transformItemOnMap({x = 32313, y = 31928, z = 08}, 2772, 2773)
		Game.sendMagicEffect({x = 32314, y = 31928, z = 08}, 12)
	elseif item:getId() == 2773 then 
		Game.transformItemOnMap({x = 32313, y = 31928, z = 08}, 2773, 2772)
		Game.sendMagicEffect({x = 32314, y = 31928, z = 08}, 12)
	end
	return true
end