function onUse(player, item, fromPosition, target, toPosition)
	if item:getId() == 2772 then
		item:transform(2773, 1)
		item:decay()
		Game.removeItemOnMap({x = 33314, y = 31592, z = 15}, 1842)
		doRelocate({x = 33316, y = 31591, z = 15},{x = 33317, y = 31591, z = 15})
		Game.createItem(1949, 1, {x = 33316, y = 31591, z = 15})
	elseif item:getId() == 2773 then 
		item:transform(2772, 1)
		item:decay()
		doRelocate({x = 33314, y = 31592, z = 15},{x = 33315, y = 31592, z = 15})
		Game.createItem(1842, 1, {x = 33314, y = 31592, z = 15})
		Game.removeItemOnMap({x = 33316, y = 31591, z = 15}, 1949)
	end
	return true
end