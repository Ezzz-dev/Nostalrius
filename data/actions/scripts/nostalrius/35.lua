function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32604, y = 31905, z = 03}, 1789)
		Game.removeItemOnMap({x = 32605, y = 31905, z = 03}, 1790)
		Game.removeItemOnMap({x = 32604, y = 31904, z = 03}, 1787)
		Game.removeItemOnMap({x = 32605, y = 31904, z = 03}, 1788)
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32604, y = 31904, z = 03},{x = 32604, y = 31906, z = 03})
		doRelocate({x = 32604, y = 31905, z = 03},{x = 32604, y = 31906, z = 03})
		doRelocate({x = 32605, y = 31904, z = 03},{x = 32605, y = 31906, z = 03})
		doRelocate({x = 32605, y = 31905, z = 03},{x = 32605, y = 31906, z = 03})
		Game.createItem(1787, 1, {x = 32604, y = 31904, z = 03})
		Game.createItem(1789, 1, {x = 32604, y = 31905, z = 03})
		Game.createItem(1788, 1, {x = 32605, y = 31904, z = 03})
		Game.createItem(1790, 1, {x = 32605, y = 31905, z = 03})
	end
	return true
end