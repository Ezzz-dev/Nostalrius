function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then 
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 33171, y = 31897, z = 08}, 1772)
	elseif item:getId() == 2773 then
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 33171, y = 31897, z = 08},{x = 33171, y = 31898, z = 08})
		Game.createItem(1772, 1, {x = 33171, y = 31897, z = 08})
	end
	return true
end