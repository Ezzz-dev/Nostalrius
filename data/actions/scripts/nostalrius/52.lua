function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32476, y = 31900, z = 04},3593) and Game.isItemThere ({x = 32477, y = 31900, z = 04},3587) and Game.isItemThere ({x = 32478, y = 31900, z = 04},3590) and Game.isItemThere ({x = 32479, y = 31900, z = 04},3585) and Game.isItemThere ({x = 32480, y = 31900, z = 04},3592) and Game.isItemThere ({x = 32481, y = 31900, z = 04},3589) then
		Game.createItem(1948, 1, {x = 32476, y = 31904, z = 04})
		Game.removeItemOnMap({x = 32476, y = 31900, z = 04}, 3593)
		Game.removeItemOnMap({x = 32477, y = 31900, z = 04}, 3587)
		Game.removeItemOnMap({x = 32478, y = 31900, z = 04}, 3590)
		Game.removeItemOnMap({x = 32479, y = 31900, z = 04}, 3585)
		Game.removeItemOnMap({x = 32480, y = 31900, z = 04}, 3592)
		Game.removeItemOnMap({x = 32481, y = 31900, z = 04}, 3589)
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2772 then
		Game.sendMagicEffect({x = 32479, y = 31905, z = 04}, 3)
	end
	return true
end