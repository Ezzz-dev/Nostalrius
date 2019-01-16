function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and not Game.isItemThere({x = 32259, y = 31891, z = 10}, 2129) then
		doRelocate({x = 32259, y = 31891, z = 10},{x = 32259, y = 31892, z = 10})
		Game.createItem(2129, 1, {x = 32259, y = 31891, z = 10})
	end
end
