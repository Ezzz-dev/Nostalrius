function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32891, y = 32590, z = 11},2567) and Game.isItemThere ({x = 32843, y = 32649, z = 11},2567) and Game.isItemThere ({x = 32808, y = 32613, z = 11},2567) and Game.isItemThere ({x = 32775, y = 32583, z = 11},2567) and Game.isItemThere ({x = 32756, y = 32494, z = 11},2567) and Game.isItemThere ({x = 32799, y = 32556, z = 11},2567) and Game.isItemThere ({x = 32864, y = 32556, z = 11},1563) then 
		item:transform(2773, 1)
		item:decay()
		Game.sendMagicEffect({x = 32864, y = 32556, z = 11}, 14)
		Game.removeItemOnMap({x = 32864, y = 32556, z = 11}, 1563)
	elseif item:getId() == 2772 and not Game.isItemThere({x = 32864, y = 32556, z = 11}, 1563) then
		player:sendCancelMessage("The lever won't budge.")
	elseif item:getId() == 2773 and not Game.isItemThere({x = 32864, y = 32556, z = 11}, 1563) then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32864, y = 32556, z = 11},{x = 32864, y = 32557, z = 11})
		Game.sendMagicEffect({x = 32864, y = 32556, z = 11}, 14)
		Game.createItem(1563, 1, {x = 32864, y = 32556, z = 11})
	elseif item:getId() == 2773 and Game.isItemThere({x = 32864, y = 32556, z = 11}, 1563) then
		item:transform(2772, 1)
		item:decay()
	end
	return true
end