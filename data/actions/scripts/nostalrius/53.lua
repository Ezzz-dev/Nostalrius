function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32478, y = 31903, z = 03},3537) and Game.isItemThere ({x = 32479, y = 31903, z = 03},3543) then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32478, y = 31903, z = 03}, 3537)
		Game.removeItemOnMap({x = 32479, y = 31903, z = 03}, 3543)
		Game.createItem(1948, 1, {x = 32479, y = 31904, z = 03})
	elseif item:getId() == 2772 then 
		Game.sendMagicEffect({x = 32478, y = 31904, z = 03}, 3)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.removeItemOnMap({x = 32479, y = 31904, z = 03}, 1948)
	end
	return true
end