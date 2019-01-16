function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32476, y = 31900, z = 06},2773) and Game.isItemThere ({x = 32477, y = 31900, z = 06},2773) and Game.isItemThere ({x = 32478, y = 31900, z = 06},2772) and Game.isItemThere ({x = 32479, y = 31900, z = 06},2772) and Game.isItemThere ({x = 32480, y = 31900, z = 06},2773) and Game.isItemThere ({x = 32481, y = 31900, z = 06}, 2772) then 
		item:transform(2773, 1)
		item:decay()
		Game.createItem(1948, 1, {x = 32476, y = 31904, z = 06})
	elseif item:getId() == 2772 then
		Game.sendMagicEffect({x = 32479, y = 31905, z = 06}, 3)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.removeItemOnMap({x = 32476, y = 31904, z = 06}, 1948)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		Game.removeItemOnMap({x = 32476, y = 31904, z = 06}, 1948)
	end
	return true
end