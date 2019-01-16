function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 and Game.isItemThere({x = 32090, y = 32148, z = 09},2772) and Game.isItemThere ({x = 32092, y = 32148, z = 09},2772) and Game.isItemThere ({x = 32094, y = 32148, z = 09},2772) and Game.isItemThere ({x = 32088, y = 32148, z = 09},2772) then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 32088, y = 32149, z = 10}, 1282)
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32088, y = 32149, z = 10},{x = 32088, y = 32150, z = 10})
		Game.createItem(1282, 1, {x = 32088, y = 32149, z = 10})
	end

	return true
end