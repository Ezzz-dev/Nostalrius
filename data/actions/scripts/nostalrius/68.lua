function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		doRelocate({x = 32225, y = 32276, z = 10},{x = 32225, y = 32275, z = 10})
		Game.createItem(1949, 1, {x = 32225, y = 32276, z = 10})
		doRelocate({x = 32233, y = 32276, z = 09},{x = 32232, y = 32276, z = 09})
		Game.createItem(1949, 1, {x = 32233, y = 32276, z = 09})
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		Game.removeItemOnMap({x = 32233, y = 32276, z = 09}, 1949)
		Game.removeItemOnMap({x = 32225, y = 32276, z = 10}, 1949)
	end
	return true
end