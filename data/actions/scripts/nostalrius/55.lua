function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then
		Game.removeItemOnMap({x = 32145, y = 32101, z = 11}, 1791)
		item:transform(2773, 1)
		item:decay()
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 32145, y = 32101, z = 11},{x = 32145, y = 32102, z = 11})
		Game.createItem(1791, 1, {x = 32145, y = 32101, z = 11})
	end
	return true
end