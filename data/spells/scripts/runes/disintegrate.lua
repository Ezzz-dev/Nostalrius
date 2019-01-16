local dead_human = {
	4240, 4241, 4242, 4247, 4248
}
local removalLimit = 10

function onCastSpell(creature, variant)
	local position = variant:getPosition()
	local tile = Tile(position)
	if tile then
		local items = tile:getItems()
		if items then
			for i, item in ipairs(items) do
				if item:getType():isMovable() and item:getActionId() == 0 and not table.contains(dead_human, item:getId()) then
					item:remove()
				end

				if i == removalLimit then
					break
				end
			end
		end
	end

	position:sendMagicEffect(CONST_ME_POFF)
	return true
end